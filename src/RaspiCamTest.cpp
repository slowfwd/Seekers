/**
@author : Vaibhav N Bhat
@description : 
	
	Contains openCV related functionality
	Uses wrapper to read frames from the camera \
	perform object (color based) detection and 
		1. Display images on the monitor for calibrating.
			or
		2. Updates a global which indicates the presence of the object 

	Contains one thread function for object detection
	Reference : Kyle Hunslow Blog
*/

#include <cv.h>
#include <highgui.h>

#include "RaspiCamCV.h"

#include <string.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "init.h"

using namespace cv;				//OpenCV namespace

#define RIGHT_THRESHOLD (500)	// Horizontal axis threshold for detecting object last went right
#define LEFT_THRESHOLD	(100)	// Horizontal axis threshold for detecting object last went left

/*** Static parameters used in this file ***/

int H_MIN = 0;					// HSV Params for detecting blue object
int H_MAX = 38;
int S_MIN = 159;
int S_MAX = 256;
int V_MIN = 93;
int V_MAX = 133;

//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=1;

//minimum and maximum object area
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;


const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";

/*** File specific static params ends here ***/


bool objectFound;		//Global variable indicating presence of the object


void on_trackbar( int, void* )
{
	
}

/** Helper function converts int to string **/

string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}


/** 
	
	Creates Trackbars on the monitor
	Used for calibrating the camera offline
	The color of the object to be detected can be set	
	Unused in the compilation for moving robot

*/
void createTrackbars(){
	//create window for trackbars


    namedWindow(trackbarWindowName,0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf( TrackbarName, "H_MIN", H_MIN);
	sprintf( TrackbarName, "H_MAX", H_MAX);
	sprintf( TrackbarName, "S_MIN", S_MIN);
	sprintf( TrackbarName, "S_MAX", S_MAX);
	sprintf( TrackbarName, "V_MIN", V_MIN);
	sprintf( TrackbarName, "V_MAX", V_MAX);

    createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar );


}


/**
@description: 
	Draws a target on the monitor to display the object on the monitor

*/

void drawObject(int x, int y,Mat &frame){
	// Indicates 
	//1. The position of the object on the frame
	//2. Indicates the area of the object
	//3. Indicates whether the object is on the left or right edge

	circle(frame,Point(x,y),20,Scalar(0,255,0),2);
    if(y-25>0)
    line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
    if(y+25<FRAME_HEIGHT)
    line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
    if(x-25>0)
    line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
    if(x+25<FRAME_WIDTH)
    line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
    else line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);

	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
	

}

// Performs erosion and dialation on the Black and White threshold image

void morphOps(Mat &thresh){


	Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));

	Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

	erode(thresh,thresh,erodeElement);
	erode(thresh,thresh,erodeElement);


	dilate(thresh,thresh,dilateElement);
	dilate(thresh,thresh,dilateElement);
	


}

/**
@description
	 1.Finds the contours of the object.
 	 2. Finds contour area 

*/

// Updates global area and flag object found

void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){
	static int cnt = 0;
	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
	//use moments method to find our filtered object
	double refArea = 0;
	
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
					x = moment.m10/area;
					y = moment.m01/area;
					objectFound = true;
					refArea = area;
				}else objectFound = false;


			}
			//let user know you found an object
			if(objectFound ==true){
				putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
				//if(cnt >=1000){
					printf("obj found: %d\n",cnt);
					fflush(stdout);
					cnt ++;
				//}
				putText(cameraFeed,intToString((int)refArea),Point(0,200),2,1,Scalar(0,0,200),2);
				if(x>RIGHT_THRESHOLD)
					putText(cameraFeed,"Obj at right edge", Point(0,300),2,1,Scalar(0,0,200),2);
				if(x<LEFT_THRESHOLD)
					putText(cameraFeed,"Obj at left edge", Point(300,450),2,1,Scalar(0,0,200),2);
				//draw object location on screen
				drawObject(x,y,cameraFeed);}

		}else {putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);}
	}
}


/**
@description : 
	Called from thread function
	Detects the color specified in the frame
	Globals:
		objectFound is updated
*/		


void startDetect()
{
	bool trackObjects = true;
	bool useMorphOps = true;

   	RaspiCamCvCapture * capture = raspiCamCvCreateCameraCapture(0); // Index doesn't really matter

	IplImage* image;
	//IplFormat image from PiCam

	
	Mat cameraFeed;
	//matrix storage for HSV image
	Mat HSV;
	//matrix storage for binary threshold image
	Mat threshold;
	//x and y values for the location of the object
	int x=0, y=0;
	//create slider bars for HSV filtering
	//createTrackbars();

	while(1){
	
		//Get frame from PiCam
		IplImage* image = raspiCamCvQueryFrame(capture);
		
		//Convert into Mat - C++ format
		cameraFeed = cvarrToMat(image,false);

		//convert frame from BGR to HSV colorspace
		cvtColor(cameraFeed,HSV,COLOR_RGB2HSV);
		//filter HSV image between values and store filtered image to
		//threshold matrix
		inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);

		if(useMorphOps)
		morphOps(threshold);

		// Thresholded frame is input object tracking function
		// x,y coordinate for the center of the object is obtained 
		// by side effect

		if(trackObjects)
			trackFilteredObject(x,y,threshold,cameraFeed);

		if(objectFound == true)
			sleep(5);	// Thread sleep - To be developed

		//show frames 
		//imshow(windowName2,threshold);
		//imshow(windowName,cameraFeed);
		//imshow(windowName1,HSV);
		
		waitKey(30);
	}

	cvDestroyWindow("RaspiCamTest");
	raspiCamCvReleaseCapture(&capture);
	//return 0;
}

/**
@description:
	Returns true if the object is too close
	Compares the area of the detected object with a ref area
*/	

bool isObjectClose()
{

}
