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
        time_t t = time(NULL);
        std::cout << trainingDataPath + "/" + faceName + "/" + std::to_string(t) + std::to_string(i) + ".jpg" << std::endl;
        cv::imwrite(trainingDataPath + "/" + faceName + "/" + std::to_string(t) + std::to_string(i) + ".jpg",
                    faces[i]);
    }
    faces.clear();
}

void FaceCaptureModel::hog()
{

}

void FaceCaptureModel::train ()
{

}
