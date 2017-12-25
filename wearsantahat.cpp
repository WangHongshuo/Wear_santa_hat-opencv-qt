#include "wearsantahat.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>

WearSantaHat::WearSantaHat()
{
    initializeData();
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

void WearSantaHat::mainTask(Mat &src)
{
    if(src.channels() == 3)
        cvtColor(src,grayImage,CV_RGB2GRAY);
    else if(src.channels() == 4)
        cvtColor(src,grayImage,CV_RGBA2BGRA);
    else
        grayImage = src.clone();
    detecteFace(grayImage);
}

void WearSantaHat::initializeData()
{
    QString Qpath = QCoreApplication::applicationDirPath();
    String path;
    Qpath += "/haarcascade_frontalface_alt2.xml";
    path = Qpath.toStdString();
    faceDetecter.load(path);
}

void WearSantaHat::detecteFace(Mat &src)
{
    outputImage = inputImage;
    std::vector<Rect> faces;
    faceDetecter.detectMultiScale(src,faces,1.2,3,0,Size(0,0));
    if(faces.size()>0)
    {
        for(int i=0; i<static_cast<int>(faces.size()); i++)
        {
            rectangle(outputImage, Point(faces[i].x, faces[i].y),
                      Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
                      Scalar(0, 0, 255, 255),2,8);
        }
    }
}
