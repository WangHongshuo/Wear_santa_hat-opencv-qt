#include "wearsantahat.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <opencv2/highgui.hpp>

WearSantaHat::WearSantaHat()
{
    initializeData();
}

WearSantaHat::~WearSantaHat()
{
    delete [] sentaHat;
}

void WearSantaHat::setImage(Mat &src)
{
    if(!src.data)
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Image data is null!"));
        msgBox.exec();
    }
    else
        inputImage = src;
    mainTask(inputImage);
}

int WearSantaHat::facePositionX(int faceIndex)
{
    if(faceIndex < faceCount)
        return facePositionData.ptr<int>(faceIndex)[0];
    else
        return -1;
}

int WearSantaHat::facePositionY(int faceIndex)
{
    if(faceIndex < faceCount)
        return facePositionData.ptr<int>(faceIndex)[1];
    else
        return -1;
}

int WearSantaHat::faceWidth(int faceIndex)
{
    if(faceIndex < faceCount)
        return facePositionData.ptr<int>(faceIndex)[2];
    else
        return -1;
}

int WearSantaHat::faceHeight(int faceIndex)
{
    if(faceIndex < faceCount)
        return facePositionData.ptr<int>(faceIndex)[3];
    else
        return -1;
}



void WearSantaHat::mainTask(Mat &src)
{
    if(src.channels() == 3)
        cvtColor(src,grayImage,CV_RGB2GRAY);
    else if(src.channels() == 4)
        cvtColor(src,grayImage,CV_RGBA2BGRA);
    else
        grayImage = src.clone();
    outputImage = src;
    detecteFace(grayImage,outputImage,facePositionData);
    addHat(outputImage,1);
}

void WearSantaHat::initializeData()
{
    QString Qpath = QCoreApplication::applicationDirPath();
    String path;
    Qpath += "/haarcascade_frontalface_alt2.xml";
    path = Qpath.toStdString();
    faceDetecter.load(path);

    Qpath = QCoreApplication::applicationDirPath();
    QString temp;
    for(int i=0;i<6;i++)
    {
        temp = Qpath + "/hat/" + QString::number(i+1) + ".png";
        path = temp.toStdString();
        sentaHat[i] = imread(path,IMREAD_UNCHANGED);
        if(!sentaHat[i].data)
        {
            QMessageBox msgBox;
            msgBox.setText(QObject::tr("Can't load hat!"));
            msgBox.exec();
            break;
        }
    }
}

void WearSantaHat::detecteFace(Mat &src, Mat &dst, Mat &facePositionData)
{
    std::vector<Rect> faces;
    faceDetecter.detectMultiScale(src,faces,1.2,3,0,Size(0,0));
    faceCount = static_cast<int>(faces.size());
    if(faces.size()>0)
    {
        facePositionData = Mat(faces.size(),4,CV_32SC1);
        for(int i=0; i<static_cast<int>(faces.size()); i++)
        {
//            rectangle(dst, Point(faces[i].x, faces[i].y),
//                      Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
//                      Scalar(0, 0, 255, 255),2,8);
            facePositionData.ptr<int>(i)[0] = faces[i].x;
            facePositionData.ptr<int>(i)[1] = faces[i].y;
            facePositionData.ptr<int>(i)[2] = faces[i].width;
            facePositionData.ptr<int>(i)[3] = faces[i].height;
        }
    }
}

void WearSantaHat::addHat(Mat &src, int hatIndex)
{
    Mat hat = sentaHat[hatIndex].clone();
    for(int i=0; i<faceCount; i++)
    {
        resize(hat,hat,Size(faceWidth(i),faceWidth(i)),INTER_CUBIC);
        Mat BGRAChannels[4];
        split(hat,BGRAChannels);
        Mat hatMask = BGRAChannels[3];
        Mat imageROI = src(Rect(facePositionX(i),facePositionY(i)-(int)(hat.rows*0.8),hat.cols,hat.rows));
        hat.copyTo(imageROI,hatMask);
    }
}
