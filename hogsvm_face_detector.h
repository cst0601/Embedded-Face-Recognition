#ifndef HOGSVM_FACE_DETECTOR
#define HOGSVM_FACE_DETECTOR

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <vector>
#include <list>

#include <dirent.h>

using namespace cv;
using namespace cv::ml;

class HogSvmFaceDetector
{
public:
    HogSvmFaceDetector (int);
    void readTrainingData (std::string);
    void readAllPersonDir (std::string path, std::vector<String> &);
    void hogsvm();
    void trainSvm(cv::Mat, cv::Mat);
    int test(cv::Mat);
private:
    const int featureAmount;
    std::vector<std::vector<Mat>> trainingData;
    cv::HOGDescriptor hogDescriptor = cv::HOGDescriptor(cv::Size(64, 64), cv::Size(16, 16),cv::Size(8, 8), cv::Size(8, 8), 9);
    Ptr<SVM> svm;
};

#endif // HOGSVM_FACE_DETECTOR

