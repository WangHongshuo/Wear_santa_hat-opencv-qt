#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ImageWidget.h"
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

void MainWindow::on_OpenFileButton_clicked()
{
    QString FilePath = QFileDialog::getOpenFileName(this,tr("Open Image"),
                                                    tr("F:/"),
                                                    tr("Image File(*.bmp *.jpg *.jpeg *.png)"));
    if(FilePath.isNull() || FilePath == "")
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Image data is null!"));
        msgBox.exec();
    }
    else
        InputImage.load(FilePath);
    ui->ShowImageWidget->set_image_with_pointer(&InputImage);
}
