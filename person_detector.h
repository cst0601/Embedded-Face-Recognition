#ifndef PERSON_DETECTOR
#define PERSON_DETECTOR

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

using namespace cv;
using namespace cv::ml;

class PersonDetector
{
public:
    PersonDetector ();
    void train();

private:
    Mat frame;
    std::vector<Mat> framePyramid;
};

#endif // PERSON_DETECTOR

