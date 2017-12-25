#include "wearsantahat.h"
#include <QMessageBox>
#include <QCoreApplication>

WearSantaHat::WearSantaHat()
{
    initializationData();
}

void WearSantaHat::setImage(Mat &input)
{
    if(!input.data == NULL)
        inputImage = input;
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Image data is null!"));
        msgBox.exec();
    }
    mainTask(inputImage);
}

void WearSantaHat::mainTask(Mat &input)
{

}

void WearSantaHat::initializationData()
{
    QString Qpath = QCoreApplication::applicationDirPath();
    String path;
    Qpath += "/haarcascade_frontalface_alt2.xml";
    path = Qpath.toStdString();
    faceDetecter.load(path);
}
