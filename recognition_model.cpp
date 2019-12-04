#include "recognition_model.h"

RecognitionModel::RecognitionModel()
{
    std::cout << "OpenCV Version used:" << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_VERSION_REVISION  << std::endl;
    svm = SVM::load("/home/nvidia/Desktop/model/people.xml");
    peopleClassifier.load("/home/nvidia/Desktop/model/haarcascades/haarcascade_frontalface_default.xml");
    //tracker = TrackerKCF::create();   // abandoned
    hogDescriptor = HOGDescriptor(Size(64, 144), Size(16, 16), Size(8, 8), Size(8, 8), 9);
}

RecognitionModel::~RecognitionModel() {}

// convert mat to pixmap. also change the color space from bgr to rgb
QPixmap RecognitionModel::mat2Pixmap (Mat input)
{
    Mat rgbFrame;
    cvtColor(input, rgbFrame, CV_BGR2RGB);
    return QPixmap::fromImage(
                QImage((unsigned char*) rgbFrame.data,
                    rgbFrame.cols,
                    rgbFrame.rows,
                    QImage::Format_RGB888)
                );
}

QPixmap RecognitionModel::getInputFrame ()
{
    inputFrame = Capturer::getInstance()->getFrame();    
    return mat2Pixmap(inputFrame);
}

QPixmap RecognitionModel::getDetectFrame ()
{
    clear();
    /* show it on opencv window */
    slidingWindow(generatePyramid(), Size(64, 144), Size(16, 32));
    //cascadeSearch();
    //showPyramid();  /* testing */
    return mat2Pixmap(inputFrame);
}

void RecognitionModel::cascadeSearch ()
{
    std::vector<Rect> peopleInstances;
    Mat grayFrame;
    cvtColor(inputFrame, grayFrame, COLOR_BGR2GRAY);
    equalizeHist(grayFrame, grayFrame);
    // detect
    peopleClassifier.detectMultiScale(grayFrame, peopleInstances, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

    faceNum = peopleInstances.size();
    for (size_t i = 0; i < peopleInstances.size(); ++i)
    {
        rectangle(inputFrame, peopleInstances[i], Scalar(0, 255, 0));
    }
}

// Generate 3 different size of image
std::vector<Mat> RecognitionModel::generatePyramid () const
{
    std::vector<Mat> pyramidFrame;
    Mat frame = inputFrame.clone();
    pyramidFrame.push_back(frame);

    for (unsigned int i = 0; i < 2; ++i)
    {
        pyrDown(frame.clone(), frame, Size(frame.cols / 2, frame.rows / 2));
        pyramidFrame.push_back(frame);
    }

    return pyramidFrame;
}

std::vector<float> RecognitionModel::hog (Mat slidedWindow)
{
    std::vector<float> feature;
    hogDescriptor.compute(slidedWindow, feature);
    return feature;
}

// Align different ROIs from different source size to the same scale
Rect RecognitionModel::roiDepyramid (Rect roi, int scale) {
    return Rect(roi.x * scale,
                roi.y * scale,
                roi.width * scale,
                roi.height * scale);
}

std::string RecognitionModel::getNumberOfFaces () const
{
    return std::to_string(faceNum);
}

// testing method, generates and show the pyramid image
void RecognitionModel::showPyramid () const
{
    std::vector<Mat> pyramidFrame = generatePyramid();
    for (unsigned int i = 0; i < 3; ++i)
    {
        cv::imshow("test_" + std::to_string(i), pyramidFrame[i]);
    }
}

// window size = 64 * 144
void RecognitionModel::slidingWindow(std::vector<Mat> image, Size windowSize, Size stride)
{
    for (unsigned int i = 0; i < image.size(); ++i)
    {
        /* slide through the whole frame */
        for (unsigned int windowY = 0; windowY + windowSize.height < image[i].rows; windowY += step.height)
        {
            for (unsigned int windowX = 0; windowX + windowSize.width < image[i].cols; windowX += step.width)
            {
                Mat roiMat = image[i](Rect(windowX, windowY, windowSize.width, windowSize.height));
                float result = svm->predict(hog(roiMat));
                rois.push_back(roiDepyramid(
                                   Rect(windowX,
                                        windowY,
                                        windowSize.width,
                                        windowSize.height),
                                   (i + 1) * 2)); // i th pyramid image
                scores.push_back(result);
            }
        }
    }
}

// Uses NMS to select useful rois
void RecognitionModel::generateInstances ()
{
    int counter = 0;
    for (unsigned int i = 0; i < scores.size(); ++i)
        if (scores[i] != -1) {
            ++counter;
            rectangle(inputFrame, rois[i], Scalar(0, 255, 0), 1);
            //std::cout << "roi area = " << rois[i].area() << std::endl;
        }
    //std::cout << "rois: " << counter << std::endl;
}

// clean all the leftovers of the last frame
void RecognitionModel::clear ()
{
    rois.clear();
    scores.clear();
    nmsIndices.clear();
}

void RecognitionModel::release ()
{
    Capturer::getInstance()->release();
}
