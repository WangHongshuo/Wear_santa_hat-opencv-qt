#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core.hpp>
#include "wearsantahat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openFileButton_clicked();

    void on_selectHatIndex_activated(int index);

private:
    void processImage(QImage &src);
    void showProcessedImage(Mat &src);
    Ui::MainWindow *ui;
    QImage qtImage;
    cv::Mat matImage;
    WearSantaHat wearMySantaHat;
    bool isImageProcessed = false;

};

#endif // MAINWINDOW_H
