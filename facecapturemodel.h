#ifndef FACECAPTUREMODEL_H
#define FACECAPTUREMODEL_H

#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

class FaceCaptureModel
{
public:
    FaceCaptureModel();
    QPixmap captureFace ();
    void release();
private:
    Mat inputFrame;
    VideoCapture video;
};

#endif // FACECAPTUREMODEL_H
