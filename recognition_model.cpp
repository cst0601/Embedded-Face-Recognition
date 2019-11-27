#include "recognition_model.h"

RecognitionModel::RecognitionModel()
    : video(0)
{
    svm = SVM::load("/home/nvidia/Desktop/model/people.xml");
    //tracker = TrackerKCF::create();
}

RecognitionModel::~RecognitionModel() {}

QPixmap RecognitionModel::getInputFrame ()
{
    video >> inputFrame;
    //read frame
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

void RecognitionModel::release ()
{
    video.release();
}
