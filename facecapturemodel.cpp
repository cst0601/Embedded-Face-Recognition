#include "facecapturemodel.h"

FaceCaptureModel::FaceCaptureModel():
    video(0)
{}

QPixmap FaceCaptureModel::captureFace ()
{
    VideoCapture video(0);
    video >> inputFrame;
    if(inputFrame.empty())
    {
        std::cout << "ERROR opening camera" << std::endl;
        throw (std::string)"empty frame";
    }
    cvtColor(inputFrame, inputFrame, CV_BGR2RGB);
    QPixmap image = QPixmap::fromImage(
                QImage((unsigned char*) inputFrame.data,
                       inputFrame.cols,
                       inputFrame.rows,
                       QImage::Format_RGB888));
    return image;
}

void FaceCaptureModel::release ()
{
    video.release();
}

