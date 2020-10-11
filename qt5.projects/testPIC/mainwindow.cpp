#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utils/logger.hpp>
#include <iostream>
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_VERBOSE);
    std::string image_path = samples::findFile("jmy_iso.png");
    Mat image = imread(image_path, IMREAD_COLOR);
    if(image.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return;
        }
    cv::imshow("OpenCV4 Test", image);
    cv::waitKey(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
