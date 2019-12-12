#ifndef FACE_DETECTOR
#define FACE_DETECTOR

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/face.hpp>
#include <opencv2/face/facerec.hpp>
#include <iostream>
#include <vector>
#include <list>

#include <dirent.h>

using namespace cv;
using namespace cv::face;

class FaceDetector
{
public:
    FaceDetector ();
    void readTrainingData (std::string);
    void readAllPersonDir (std::string path, std::vector<std::string> &);
    void train();
    std::string getNameById(int);
    std::string test(cv::Mat);
private:
    std::vector<Mat> trainingImage;
    std::vector<int> label;
    std::vector<std::string> personName;
    Ptr<FaceRecognizer> model;
};

#endif // HOGSVM_FACE_DETECTOR

