#ifndef MODEL
#define MODEL

#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/ml/ml.hpp>

using namespace cv;
using namespace cv::ml;

class RecognitionModel
{
public:
    RecognitionModel();
    ~RecognitionModel();
    QPixmap getInputFrame ();
    void release();

private:
    VideoCapture video;
    Mat inputFrame;
    Ptr<SVM> svm;
};

#endif // MODEL

