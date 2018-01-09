#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QImageMatConvert/mat_qimage_convert.h"
#include "ImageWidget-Qt/ImageWidget.h"
#include <QFileDialog>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked()
{
    QString FilePath = QFileDialog::getOpenFileName(this,tr("Open Image"),
                                                    tr("F:/Qt_project/Wear_santa_hat-opencv-qt/test_image/"),
                                                    tr("Image File(*.bmp *.jpg *.jpeg *.png)"));
    if(FilePath.isNull() || FilePath == "")
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Image data is null!"));
        msgBox.exec();
    }
    else
    {
        qtImage.load(FilePath);
        processImage(qtImage);
    }
}

void MainWindow::processImage(QImage &src)
{
    matImage = QImage2Mat_with_data(src);
    QTime a;
    a.start();
    wearMySantaHat.putOnMySantaHat(matImage);
    qDebug() << a.elapsed();
    isImageProcessed = true;
    showProcessedImage(wearMySantaHat.outputImage);
}

void MainWindow::showProcessedImage(Mat &src)
{
    qtImage = Mat2QImage_with_pointer(src);
    ui->showImageWidget->set_image_with_pointer(&qtImage);
}

void MainWindow::on_selectHatIndex_activated(int index)
{
    if(isImageProcessed)
    {
        wearMySantaHat.updateHat(index);
        showProcessedImage(wearMySantaHat.outputImage);
    }
}
