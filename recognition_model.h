#ifndef MODEL
#define MODEL

#include <string>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/ml/ml.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/objdetect.hpp>

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
    std::vector<Mat> generatePyramid();
    std::vector<float> hog(Mat);
    Rect roiDepyramid(Rect, int);
    std::string getNumberOfFaces () const;
    void slidingWindow(std::vector<Mat>, Size, Size);
    void generateInstances();
    void clear();
    void release();


private:
    VideoCapture video;
    Mat inputFrame;

    unsigned int faceNum = 0, personNum = 0;

    Ptr<SVM> svm;
    Ptr<Tracker> tracker;
    CascadeClassifier peopleClassifier;
    CascadeClassifier faceClassifier;
    std::vector<Rect> rois;
    std::vector<float> scores;
    std::vector<int> nmsIndices;
    HOGDescriptor hogDescriptor;
};

#endif // MODEL

