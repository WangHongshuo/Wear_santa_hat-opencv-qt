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
    void setImage(Mat &input);

private:
    void mainTask(Mat &input);
    void initializationData();
    Mat inputImage;
    Mat outputImage;
    CascadeClassifier faceDetecter;
};

#endif // WEARSANTAHAT_H
