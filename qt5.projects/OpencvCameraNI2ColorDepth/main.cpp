
#include "OpenNI.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

// OpenCV Header
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

using namespace openni;


/*
 * Depth Max/Min adjust
 *
 */
cv::Mat adjustDepth(const cv::Mat& inImage)
{
    // from https://orbbec3d.com/product-astra/
    // Astra S has a depth in the range 0.35m to 2.5m
    //int maxDepth = 2500;
    //int minDepth = 350; // in mm
    // Astra Pro has a depth in the range 0.6m to 8m
    int maxDepth = 3000;
    int minDepth = 600; // in mm

    cv::Mat retImage = inImage;

    for(int j = 0; j < retImage.rows; j++)
        for(int i = 0; i < retImage.cols; i++) {
            if (retImage.at<ushort>(j, i) < maxDepth) //convert points in range
                retImage.at<ushort>(j, i) = maxDepth - (retImage.at<ushort>(j, i) - minDepth);
            else
                retImage.at<ushort>(j, i) = 10; //dark it
            }

        return retImage;
}




int main(int argc, char* argv[])
{
    auto version = openni::OpenNI::getVersion();
    std::cout << "OpenNI " << version.major << "." << version.minor << "." <<
                               version.maintenance << "." << version.build << std::endl;

    VideoFrameRef oniDepthImg, oniColorImg;

    OpenNI::shutdown();

    Status result = STATUS_OK;
    result = OpenNI::initialize();

    // open device
    Device device;
    result = device.open( openni::ANY_DEVICE );


    //// create color stream
    VideoStream oniColorStream;
    result = oniColorStream.create( device, openni::SENSOR_IR );
    //// create depth stream
    VideoStream oniDepthStream;
    result = oniDepthStream.create( device, openni::SENSOR_DEPTH );

    // set depth video mode
    VideoMode modeDepth;
    modeDepth.setResolution( 640, 480 );
    modeDepth.setFps( 30 );
    modeDepth.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );
    oniDepthStream.setVideoMode(modeDepth);
    //oniDepthStream.setMirroringEnabled(true);
    //device.setImageRegistrationMode(ImageRegistrationMode::IMAGE_REGISTRATION_DEPTH_TO_COLOR);

    VideoMode modeColor;
    modeColor.setResolution( 640, 480 );
    modeColor.setFps( 30 );
    modeColor.setPixelFormat( PIXEL_FORMAT_RGB888 );
    oniColorStream.setVideoMode(modeColor);

    device.setImageRegistrationMode(ImageRegistrationMode::IMAGE_REGISTRATION_DEPTH_TO_COLOR);

    // start depth stream
    result = oniColorStream.start();
    result = oniDepthStream.start();
    while( true ) {

        if (oniColorStream.isValid()) {
        if ( oniColorStream.readFrame( &oniColorImg ) == STATUS_OK ) {
            cv::Mat cColorImg( oniColorImg.getHeight(), oniColorImg.getWidth(),
                CV_8UC3, (void*)oniColorImg.getData() );

            cv::Mat frameColor;
            cv::cvtColor(cColorImg, frameColor, COLOR_BGR2GRAY); //this will put colors right
            cv::imshow("Structured IR", frameColor);
            moveWindow("Structured IR", oniColorImg.getWidth()+8, 0 );
            }
        }

        if ( oniDepthStream.readFrame( &oniDepthImg ) == STATUS_OK ) {
            cv::Mat cDepthImg( oniDepthImg.getHeight(), oniDepthImg.getWidth(),
                CV_16UC1, (void*)oniDepthImg.getData() );

             cv::Mat adjustedDepth = adjustDepth(cDepthImg);
             cv::Mat dispImage;
             adjustedDepth.convertTo(dispImage, CV_8UC1, 255.0f/4000); //Darker
             cv::imshow("Adjusted Depth", dispImage);
             moveWindow("Adjusted Depth", 0, 0 );
            }

        waitKey(10);
        }
    oniColorStream.destroy();
    oniDepthStream.destroy();

    device.close();
    OpenNI::shutdown();
    //return 0;
}
