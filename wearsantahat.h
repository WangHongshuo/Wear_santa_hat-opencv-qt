#ifndef WEARSANTAHAT_H
#define WEARSANTAHAT_H
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;

class WearSantaHat
{
public:
    WearSantaHat();
    void setImage(Mat &src);
    Mat outputImage;

private:
    void mainTask(Mat &src);
    void initializeData();
    void detecteFace(Mat &src);
    Mat inputImage;
    Mat grayImage;

    CascadeClassifier faceDetecter;
};

#endif // WEARSANTAHAT_H
