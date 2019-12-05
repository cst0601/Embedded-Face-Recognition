#ifndef HAAR_FACE_DETECTOR
#define HAAR_FACE_DETECTOR

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <vector>

using namespace cv;

/*
 * HaarFaceDetector
 * Uses CascadeClassifier to detect face
 */
class HaarFaceDetector
{
public:
    HaarFaceDetector ();
    std::vector<Rect> searchFace (Mat);
private:
    CascadeClassifier faceClassifier;
};

#endif // HAAR_FACE_DETECTOR

