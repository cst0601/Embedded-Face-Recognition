#include "recognition_model.h"

RecognitionModel::RecognitionModel():
    faceRecognizer(12996)
{
    std::cout << "OpenCV Version used:" << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_VERSION_REVISION  << std::endl;
    svm = SVM::load("/home/nvidia/Desktop/model/people.xml");
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
    cascadeSearch();
    //showPyramid();  /* testing */
    generateInstances();
    //imshow("detect", inputFrame);
    return mat2Pixmap(inputFrame);
}

void RecognitionModel::cascadeSearch ()
{
    std::vector<Rect> peopleInstances = faceDetector.searchFace(inputFrame);
    faceNum = peopleInstances.size();
    for (size_t i = 0; i < peopleInstances.size(); ++i)
    {
        rectangle(inputFrame, peopleInstances[i], Scalar(255, 0, 0), 2);
    }
}

// Generate 3 different size of image
std::vector<Mat> RecognitionModel::generatePyramid () const
{
    std::vector<Mat> pyramidFrame;
    Mat frame = inputFrame.clone();
    pyramidFrame.push_back(frame);

    for (unsigned int i = 0; i < 3; ++i)
    {
        pyrDown(frame.clone(), frame, Size(int(frame.cols / 2),
                                           int(frame.rows / 2)));
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

std::string RecognitionModel::getNumberOfPeople () const
{
    return std::to_string(nmsRoi.size());
}

int RecognitionModel::getAreaOfOverlap(const Rect & r1, const Rect & r2) const
{
    Rect overlapRect = r1 | r2;
    return overlapRect.area();
}

int RecognitionModel::getAreaOfUnion(const Rect & r1, const Rect & r2) const
{
    Rect unionRect = r1 & r2;
    return unionRect.area();
}

double RecognitionModel::getIoU(Rect r1, Rect r2) const
{
    int unionArea = getAreaOfUnion(r1, r2);
    if (unionArea == 0)
        return 0;
    return getAreaOfOverlap(r1, r2) / unionArea;
}

// testing method, generates and show the pyramid image
void RecognitionModel::showPyramid () const
{
    std::vector<Mat> pyramidFrame = generatePyramid();
    for (unsigned int i = 0; i < 3; ++i)
    {
        //cv::imshow("test_" + std::to_string(i), pyramidFrame[i]);
    }
}

// window size = 64 * 144
void RecognitionModel::slidingWindow(std::vector<Mat> image, Size windowSize, Size stride)
{
    #pragma omp parallel for    // <--- cheating :)
    for (unsigned int i = 0; i < image.size(); ++i)
    {
        /* slide through the whole frame */
        for (unsigned int windowY = 0; windowY + windowSize.height < image[i].rows; windowY += stride.height)
        {
            for (unsigned int windowX = 0; windowX + windowSize.width < image[i].cols; windowX += stride.width)
            {
                Mat roiMat = image[i](Rect(windowX, windowY, windowSize.width, windowSize.height));
                if (svm->predict(hog(roiMat)) != -1)    // if detect person
                {
                    rois.push_back(roiDepyramid(
                                       Rect(windowX,
                                            windowY,
                                            windowSize.width,
                                            windowSize.height),
                                       (i + 1) * 2)); // i th pyramid image
                }
            }
        }
    }
}

// Uses NMS to select useful rois
void RecognitionModel::generateInstances ()
{
    NMS();
    for (unsigned int i = 0; i < nmsRoi.size(); ++i)
    {
        rectangle(inputFrame, nmsRoi[i], Scalar(0, 255, 0), 2);   /* for testing */
    }
}

void RecognitionModel::NMS ()
{
    nmsRoi.push_back(rois[0]);
    for (unsigned int i = 1; i < rois.size(); ++i)
    {
        bool independentRoi = true;
        for (unsigned int j = 0; j < nmsRoi.size(); ++j)
        {
            if (getIoU(nmsRoi[j], rois[i]) > roiThreshold) {
                independentRoi = false;
                break;
            }
        }
        if (independentRoi)
            nmsRoi.push_back(rois[i]);
    }
}

int RecognitionModel::predictFace()
{
    // preprocess
    int faceFlag = 0;       // flag show if face is detected
    std::vector<Rect> faces = faceDetector.searchFace(inputFrame);
    if (faces.size() == 0)
        faceFlag = -1;          // no faces detected in input image
    Mat dst = inputFrame(faces[0]);  // crop 1 face in image for training data
    resize(dst, dst, Size(160, 160));

    if (faceFlag == 0)
    {
        return faceRecognizer.test(dst);
    }
    return -1;
}

// clean all the leftovers of the last frame
void RecognitionModel::clear ()
{
    nmsRoi.clear();
    rois.clear();
}

void RecognitionModel::release ()
{
    Capturer::getInstance()->release();
}
