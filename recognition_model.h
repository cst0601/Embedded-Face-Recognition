#ifndef MODEL
#define MODEL

#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

class RecognitionModel
{
public:
    RecognitionModel();
    ~RecognitionModel();
    QPixmap getInputFrame ();

private:
    cv::VideoCapture video;
    cv::Mat inputFrame;
};

#endif // MODEL

