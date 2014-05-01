
/**
Purpose : 
		  Camera used - Raspberry Pi Camera

		  Contains wrapper functions for making compatible camera specific
		  interface to OpenCV interface 
*/


#ifndef __RaspiCamCV__
#define __RaspiCamCV__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _RASPIVID_STATE RASPIVID_STATE;

typedef struct {
	RASPIVID_STATE * pState;
} RaspiCamCvCapture;

typedef struct _IplImage IplImage;		//OpenCV standard image matrix

RaspiCamCvCapture * raspiCamCvCreateCameraCapture(int index);	//For creating camera instance
void raspiCamCvReleaseCapture(RaspiCamCvCapture ** capture);	// For destroying the camera instance
void raspiCamCvSetCaptureProperty(RaspiCamCvCapture * capture, int property_id, double value);
IplImage * raspiCamCvQueryFrame(RaspiCamCvCapture * capture);	// Returns the IplImage (image matrix) of the camera instance

#ifdef __cplusplus
}
#endif

#endif
