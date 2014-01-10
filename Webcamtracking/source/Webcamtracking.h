#ifndef _WEBCAMTRACKING_H
#define _WEBCAMTRACKING_H
#include "VideoEngine.h"
#include "DetectFaces.h"
#include "DetectEyes.h"
#include "DrawOnFace.h"
using namespace cv;

class Webcamtracking: public VideoEngine
{
public:
	Webcamtracking(void);
	~Webcamtracking(void);
	virtual void calcButtonsize(const cv::Mat& videoFrame);
	virtual void processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame);
	virtual void showProcessedFrame(const cv::Mat&processedFrame);
private:
	//cv::Mat firstFrame;
	DetectFaces facedetector;
	DetectEyes eyesdetector;
	DrawOnFace drawOnFace;

	bool debugDraw;
	bool overlayImages;
	bool detectEyes;
	bool flipImg;
	
	bool rescaleButtons;
	int buttonHeight;
	int buttonWidth;
	int buttonAnz;
	Mat changeglasses;
	Mat changehat;
	Mat screenshot;


	Mat showglassesOff;
	Mat showglassesOn;
	Mat showhatOff;
	Mat showhatOn;
	
	bool showglasses;
	bool showhat;
};
#endif