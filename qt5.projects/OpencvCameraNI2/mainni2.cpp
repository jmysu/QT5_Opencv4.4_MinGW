// Sample_Depth_UVC_Viewer.cpp : 隅砱諷秶怢茼蚚最唗腔諳萸﹝
//

//#include "stdafx.h"

#include "OpenNI.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

// OpenCV Header
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

using namespace openni;

int main(int argc, char* argv[])
{
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
    modeDepth.setFps( 60 );
    modeDepth.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );
    oniDepthStream.setVideoMode(modeDepth);
    //oniDepthStream.setMirroringEnabled(true);
    device.setImageRegistrationMode(ImageRegistrationMode::IMAGE_REGISTRATION_DEPTH_TO_COLOR);

    VideoCapture cap;
    cap.open(1); //Astra on USB list #1
    if(!cap.isOpened())
        return false;

    //cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    cap.set(CAP_PROP_FRAME_WIDTH,640); //Opencv4
    cap.set(CAP_PROP_FRAME_HEIGHT,480);//Opencv4

    // start depth stream
    result = oniDepthStream.start();
    while( true )
    {

        Mat frame,rgb;
        cap>>frame;

        if(frame.empty())
            break;
        //cvtColor(frame,rgb,CV_RGB2GRAY);
        cvtColor(frame,rgb, COLOR_RGB2GRAY);//Opencv4


        if( oniDepthStream.readFrame( &oniDepthImg ) == STATUS_OK )
        {

            cv::Mat cDepthImg( oniDepthImg.getHeight(), oniDepthImg.getWidth(),
                CV_16UC1, (void*)oniDepthImg.getData() );

            cv::Mat c8BitDepth,c24Bit;
            cDepthImg.convertTo( c8BitDepth, CV_8U, 255.0 / (8000) );

            Mat dst;
            addWeighted(c8BitDepth,0.5,rgb,0.5,0,dst);
            cv::imshow( "Orbbec", dst );

        }
        waitKey(10);
    }

    oniDepthStream.destroy();



    device.close();
    OpenNI::shutdown();
    //return 0;
}

