#ifndef MODEL
#define MODEL

#include <string>
#include <omp.h>

#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect.hpp>

#include "capturer.h"
#include "haar_face_detector.h"

using namespace cv;
using namespace cv::ml;

class RecognitionModel
{
public:
    RecognitionModel();
    ~RecognitionModel();
    QPixmap mat2Pixmap(Mat);
    QPixmap getInputFrame ();
    QPixmap getDetectFrame();
    void cascadeSearch();
    std::vector<Mat> generatePyramid() const;
    std::vector<float> hog(Mat);
    Rect roiDepyramid(Rect, int);
    std::string getNumberOfFaces () const;
    std::string getNumberOfPeople () const;
    int getAreaOfOverlap(const Rect &, const Rect &) const;
    int getAreaOfUnion(const Rect &, const Rect &) const;
    double getIoU(Rect, Rect) const;
    void showPyramid () const;
    void slidingWindow(std::vector<Mat>, Size, Size);
    void generateInstances();
    void NMS();
    void clear();
    void release();


private:
    Mat inputFrame;
    unsigned int faceNum = 0, personNum = 0;
    const double roiThreshold = 0.5;
    const double pyramidScale = 1.5;

    Ptr<SVM> svm;
    HaarFaceDetector faceDetector;
    std::vector<Rect> rois;
    std::vector<Rect> nmsRoi;
    HOGDescriptor hogDescriptor;
};

#endif // MODEL

