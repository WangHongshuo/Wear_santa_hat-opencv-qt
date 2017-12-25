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
    ~WearSantaHat();
    void setImage(Mat &src);
    Mat outputImage;
    int faceCount = -1;
    int facePositionX(int faceIndex);
    int facePositionY(int faceIndex);
    int faceWidth(int faceIndex);
    int faceHeight(int faceIndex);

private:
    void mainTask(Mat &src);
    void initializeData();
    void detecteFace(Mat &src, Mat &dst, Mat &facePositionData);
    void addHat(Mat &src, int hatIndex);
    Mat *sentaHat = new Mat[6];
    Mat inputImage;
    Mat grayImage;
    Mat facePositionData;

    CascadeClassifier faceDetecter;
};

#endif // WEARSANTAHAT_H
