#include "wearsantahat.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QTime>
#include <opencv2/highgui.hpp>

WearSantaHat::WearSantaHat()
{
    initializeData();
}

WearSantaHat::~WearSantaHat()
{
    delete [] sentaHat;
}

void WearSantaHat::putOnMySantaHat(Mat &src)
{
    if(!src.data)
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Image data is null!"));
        msgBox.exec();
    }
    else if(!isInitializationSuccess)
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Initialization Failed!"));
        msgBox.exec();
    }
    else
    {
        inputImage = src;
        mainTask(inputImage);
    }
}

void WearSantaHat::updateHat(int hat)
{
    if(hat > 6)
        hat = 5;
    hatIndex = hat;
    addHat(inputImage,outputImage,hatIndex);
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

void WearSantaHat::selectHat(int index)
{
    hatIndex = index;
}

void WearSantaHat::mainTask(Mat &src)
{
    if(src.channels() == 3)
        cvtColor(src,grayImage,CV_RGB2GRAY);
    else if(src.channels() == 4)
        cvtColor(src,grayImage,CV_RGBA2BGRA);
    else
        grayImage = src.clone();
    detecteFace(grayImage,facePositionData);
    addHat(inputImage,outputImage,hatIndex);
}

void WearSantaHat::initializeData()
{
    QString Qpath = QCoreApplication::applicationDirPath();
    String path;
    Qpath += "/haarcascade_frontalface_alt2.xml";
    path = Qpath.toStdString();
    faceDetecter.load(path);
    if(faceDetecter.empty())
    {
        isInitializationSuccess = false;
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Can't load detecer data!"));
        msgBox.exec();
    }
    Qpath = QCoreApplication::applicationDirPath();
    QString temp;
    for(int i=0;i<6;i++)
    {
        temp = Qpath + "/hat/" + QString::number(i+1) + ".png";
        path = temp.toStdString();
        sentaHat[i] = imread(path,IMREAD_UNCHANGED);
        if(!sentaHat[i].data)
        {
            isInitializationSuccess = false;
            QMessageBox msgBox;
            msgBox.setText(QObject::tr("Can't load hat!"));
            msgBox.exec();
            break;
        }
    }
}

void WearSantaHat::detecteFace(Mat &src,Mat &facePositionData)
{
//    QTime a;
//    a.start();
    std::vector<Rect> faces;
    faceDetecter.detectMultiScale(src,faces,1.2,3,0,Size(0,0));
//    qDebug() << a.elapsed();
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

void WearSantaHat::addHat(Mat &src, Mat &dst, int hatIndex)
{
    int srcX1, srcY1, srcX2, srcY2;
    dst = src.clone();
    if(faceCount > 0)
    {
        for(int i=0; i<faceCount; i++)
        {
            Mat hat = sentaHat[hatIndex].clone();
            int hatSize = int(faceWidth(i)*hatScale[hatIndex]);
            resize(hat,hat,Size(hatSize,hatSize),INTER_CUBIC);
            int hatX1 = 0, hatY1 = 0, hatX2 = hatSize-1, hatY2 = hatSize-1;

            Mat BGRAChannels[4];
            split(hat,BGRAChannels);
            Mat hatMask = BGRAChannels[3];

            // hat是4通道图片，如果输入图片为3或1通道，转换一下
            if(src.channels() == 3)
            {
                Mat temp[3] = {BGRAChannels[0],BGRAChannels[1],BGRAChannels[2]};
                merge(temp,3,hat);
            }
            else if (src.channels() == 1)
            {
                Mat temp[4] = {src, src, src, src};
                merge(temp,4,dst);
            }


            srcX1 = facePositionX(i) - int((0.5*(hatScale[hatIndex]-1.0f))*faceWidth(i));
            srcY1 = facePositionY(i) - int(hat.rows*hatYScale[hatIndex]);
            srcX2 = srcX1 + hatSize - 1;
            srcY2 = srcY1 + hatSize - 1;
            // 防止越界
            if(srcX1 < 0)
            {
                hatX1 = -srcX1;
                srcX1 = 0;
            }
            if(srcY1 < 0)
            {
                hatY1 = -srcY1;
                srcY1 = 0;
            }
            if(srcX2 > src.cols-1)
            {
                hatX2 = hatX2-(srcX2-src.cols+1);
                srcX2 = src.cols-1;
            }
            if(srcY2 > src.rows-1)
            {
                hatY2 = hatY2-(srcY2-src.rows+1);
                srcY2 = src.rows-1;
            }

            Mat imageROI = dst(Rect(srcX1,srcY1,srcX2-srcX1+1,srcY2-srcY1+1));
            Mat hatROI = hat(Rect(hatX1,hatY1,hatX2-hatX1+1,hatY2-hatY1+1));
            Mat hatMaskROI = hatMask(Rect(hatX1,hatY1,hatX2-hatX1+1,hatY2-hatY1+1));
            hatROI.copyTo(imageROI,hatMaskROI);
        }
    }
}


