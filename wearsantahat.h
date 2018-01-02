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
    void putOnMySantaHat(Mat &src);
    void updateHat(int hat);
    Mat outputImage;
    int faceCount = -1;
    int facePositionX(int faceIndex);
    int facePositionY(int faceIndex);
    int faceWidth(int faceIndex);
    int faceHeight(int faceIndex);
    void selectHat(int index);

private:
    void mainTask(Mat &src);
    void initializeData();
    void detecteFace(Mat &src, Mat &facePositionData);
    void addHat(Mat &src, Mat &dst, int hatIndex);
    Mat *sentaHat = new Mat[6];
    Mat inputImage;
    Mat grayImage;
    Mat facePositionData;
    int hatIndex = 0;
    bool isInitializationSuccess = true;
    CascadeClassifier faceDetecter;
    float hatScale[6] = {1.6f,1.3f,1.4f,1.5f,1.3f,1.6f};
    float hatYScale[6] = {1.0f,1.0f,1.0f,1.0f,1.0f,0.7f};
};

#endif // WEARSANTAHAT_H
