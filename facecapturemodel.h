#ifndef FACECAPTUREMODEL_H
#define FACECAPTUREMODEL_H

#include <QPixmap>
#include <time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "capturer.h"
#include "haar_face_detector.h"
#include "face_detector.h"

using namespace cv;

/*
 * FaceCaptureModel
 * For capturing new face and train it
 *
 */
class FaceCaptureModel
{
public:
    FaceCaptureModel();
    QPixmap captureFace ();
    int trainingDataPreprocess(const Mat &, Mat &);
    void pushFrameToData ();
    void setFaceName (std::string);
    void saveTrainingData();
    void train();
private:
    Mat frame;
    HaarFaceDetector faceDetector;
    std::vector<Mat> faces;
    const std::string trainingDataPath = "/home/nvidia/Desktop/face_data";
    std::string faceName = "_default";
};

#endif // FACECAPTUREMODEL_H
