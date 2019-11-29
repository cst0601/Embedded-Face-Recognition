#include "facecapturemodel.h"

FaceCaptureModel::FaceCaptureModel() {}

QPixmap FaceCaptureModel::captureFace ()
{
    Mat frame = Capturer::getInstance()->getFrame();
    faces.push_back(frame);
    cvtColor(frame, frame, CV_BGR2RGB);
    return QPixmap::fromImage(
                QImage((unsigned char*) frame.data,
                    frame.cols,
                    frame.rows,
                    QImage::Format_RGB888)
                );
}

void FaceCaptureModel::setFaceName (std::string name)
{
    faceName = name;
}

// save the captured frame with name
void FaceCaptureModel::saveTrainingData()
{
    system(("mkdir -p " + trainingDataPath + "/" + faceName).c_str());
}

void FaceCaptureModel::hog()
{

}

void FaceCaptureModel::train ()
{

}
