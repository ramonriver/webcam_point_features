
//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

//eigen
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

//consts
const unsigned int MIN_NUM_FEATURES = 300; //minimum number of point fetaures

int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
	int cam_id; //camera id . Associated to device number in /dev/videoX
    cv::Ptr<cv::ORB> orb_detector = cv::ORB::create(); //ORB point feature detector
    orb_detector->setMaxFeatures(MIN_NUM_FEATURES);
    std::vector<cv::KeyPoint> point_set; //set of point features
    cv::Mat descriptor_set; //set of descriptors, for each feature there is an associated descriptor

	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		{
            std::cout << "No image" << std::endl;
            cv::waitKey();
        }

    //**************** Find ORB point fetaures and descriptors ****************************

        //clear previous points
        point_set.clear();

        //detect and compute(extract) features

        //detecció amb màscara per agafar només una regió d'interès "roi" (posar valors diferents de 0)
        // CV_8UC1 ha de ser 1 channel, no funciona amb 3 channel CV_8UC3
        cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);  //NOTE: using the type explicitly

        //amb aquest tipus de definició de matriu, es defineixen punters, de manera que el modificar "roi"
        //   també es modifica l'original "mask"
        //   cv::Rect(x,y,widht, height) --> punt x,y del cantó  del rectangle i amplada i alçada
        cv::Mat roi(mask, cv::Rect(10,10,200,200));
        roi = cv::Scalar(255, 255, 255);

        orb_detector->detectAndCompute(image, mask, point_set, descriptor_set);

        //detecció sense màscara per agafar tota la imatge
        //orb_detector->detectAndCompute(image, cv::noArray(), point_set, descriptor_set);

        //draw points on the image
        cv::drawKeypoints( image, point_set, image, 255, cv::DrawMatchesFlags::DEFAULT );

    //********************************************************************

        //show image
        cv::imshow("Output Window", image);

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
    }
}
