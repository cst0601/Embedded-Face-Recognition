#include "facecapturemodel.h"

FaceCaptureModel::FaceCaptureModel() {}

QPixmap FaceCaptureModel::captureFace ()
{
    frame = Capturer::getInstance()->getFrame();
    Mat output;
    cvtColor(frame, output, COLOR_BGR2RGB);
    return QPixmap::fromImage(
                QImage((unsigned char*) output.data,
                    output.cols,
                    output.rows,
                    QImage::Format_RGB888)
                );
}

void FaceCaptureModel::pushFrameToData ()
{
    faces.push_back(frame);
    std::cout << "push" << std::endl;
}

void FaceCaptureModel::setFaceName (std::string name)
{
    faceName = name;
}

// save the captured frame with name
void FaceCaptureModel::saveTrainingData()
{
    system(("mkdir -p " + trainingDataPath + "/" + faceName).c_str());
    for(int i = 0; i < faces.size(); i++)
    {
        Mat trainingImage;
        int imageSig = trainingDataPreprocess(faces[i], trainingImage);
        if (imageSig == 0)
        {
            time_t t = time(NULL);
            std::string filePath = trainingDataPath + "/" + faceName + "/" + std::to_string(t) + std::to_string(i) + ".jpg";
            std::cout << "saving: " << filePath << std::endl;
            cv::imwrite(filePath, trainingImage);
        }
    }
    faces.clear();
    train();
}

// generate list of face in 160 * 160,
// only captures 1 if many faces appear in input image
int FaceCaptureModel::trainingDataPreprocess(const Mat & image, Mat & dst)
{
    std::vector<Rect> faces = faceDetector.searchFace(image);
    if (faces.size() == 0)
        return -1;          // no faces detected in input image
    dst = image(faces[0]);  // crop 1 face in image for training data
    resize(dst, dst, Size(160, 160));
    return 0;
}

void FaceCaptureModel::train ()
{
    std::cout << "**train" << std::endl;
    FaceDetector detector;
    detector.readTrainingData("/home/nvidia/Desktop/face_data/");
    detector.train();
}
