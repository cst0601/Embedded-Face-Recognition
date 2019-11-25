#include "recognition_model.h"

RecognitionModel::RecognitionModel()
    : video(0)
{ }

RecognitionModel::~RecognitionModel()
{
    video.release();
}

QPixmap RecognitionModel::getInputFrame ()
{
    video >> inputFrame;
    //read frame
    if(inputFrame.empty())
    {
        throw (std::string)"empty frame";
    }
    cv::cvtColor(inputFrame, inputFrame, CV_BGR2RGB);
    QPixmap image = QPixmap::fromImage(
                QImage((unsigned char*) inputFrame.data,
                       inputFrame.cols,
                       inputFrame.rows,
                       QImage::Format_RGB888));
    return image;
}
