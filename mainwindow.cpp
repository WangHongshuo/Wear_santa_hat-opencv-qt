#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ImageWidget.h"
#include "mat_qimage_convert.h"
#include <QFileDialog>

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
    wearMySantaHat.setImage(matImage);
    qtImage = Mat2QImage_with_pointer(wearMySantaHat.outputImage);
    ui->showImageWidget->set_image_with_pointer(&qtImage);
    qDebug() << wearMySantaHat.facePositionX(0);
}
