#ifndef HOGSVM_FACE_DETECTOR
#define HOGSVM_FACE_DETECTOR

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>
#include <vector>
#include <list>

using namespace cv;

class HogSvmFaceDetector
{
public:
    HogSvmFaceDetector (int);
    void readTrainingData (std::string);
private:
    const int featureAmount;
    std::list<std::vector<Mat>> trainingData;
};

#endif // HOGSVM_FACE_DETECTOR

