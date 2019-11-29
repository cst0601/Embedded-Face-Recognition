#ifndef FACECAPTUREMODEL_H
#define FACECAPTUREMODEL_H

#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "capturer.h"

using namespace cv;

class FaceCaptureModel
{
public:
    FaceCaptureModel();
    QPixmap captureFace ();
    void setFaceName (std::string);
    void saveTrainingData();
    void hog();
    void train();
private:
    std::vector<Mat> faces;
    const std::string trainingDataPath = "face_data";
    std::string faceName = "(default)";
};

#endif // FACECAPTUREMODEL_H
