
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

    VideoFrameRef oniDepthImg;

    OpenNI::shutdown();

    Status result = STATUS_OK;
    result = OpenNI::initialize();

    // open device
    Device device;
    result = device.open( openni::ANY_DEVICE );


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
    device.setImageRegistrationMode(ImageRegistrationMode::IMAGE_REGISTRATION_DEPTH_TO_COLOR);

    /*
    //Set UVC camera capture
    VideoCapture cap;
    cap.open(1); //Astra on USB list #1
    if(!cap.isOpened())
        return false;
    cap.set(CAP_PROP_FRAME_WIDTH,720); //Opencv4
    cap.set(CAP_PROP_FRAME_HEIGHT,480);//Opencv4
    */


    // start depth stream
    result = oniDepthStream.start();
    while( true ) {

        /*
        //Capture UVC
        //Mat frame,rgb;
        //cap>>frame;
        //if(frame.empty())
        //    break;
        //cvtColor(frame,rgb,CV_RGB2GRAY);
        //cvtColor(frame,rgb, COLOR_RGB2GRAY);//Opencv4
        */

        if ( oniDepthStream.readFrame( &oniDepthImg ) == STATUS_OK ) {
            cv::Mat cDepthImg( oniDepthImg.getHeight(), oniDepthImg.getWidth(),
                CV_16UC1, (void*)oniDepthImg.getData() );

            //cv::Mat c8BitDepth,c24Bit;
            //cDepthImg.convertTo( c8BitDepth, CV_8U, 255.0 / (1000) );

            //Mat dst;
            //addWeighted(c8BitDepth,0.5,rgb,0.5,0,dst);
            //cv::imshow( "Astra Depth", dst );
            //cv::imshow( "Astra Depth", cDepthImg);


             cv::Mat adjustedDepth = adjustDepth(cDepthImg);
             cv::Mat dispImage;
             adjustedDepth.convertTo(dispImage, CV_8UC1, 255.0f/4000); //Darker
             cv::imshow("Adjusted Depth", dispImage);
            }

        waitKey(10);
        }

    oniDepthStream.destroy();

    device.close();
    OpenNI::shutdown();
    //return 0;
}
