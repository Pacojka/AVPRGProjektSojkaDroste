#ifndef _WEBCAMTRACKING_H
#define _WEBCAMTRACKING_H
#include "VideoEngine.h"
#include "DetectFaces.h"
#include "DetectEyes.h"
#include "DrawOnFace.h"
#include "DrawEnvironment.h"
using namespace cv;

class Webcamtracking: public VideoEngine
{
public:
	Webcamtracking(void);
	~Webcamtracking(void);
	virtual void calcAssetssize(const cv::Mat& videoFrame);
	virtual void processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame);
	virtual void showProcessedFrame(const cv::Mat&processedFrame);
private:
	//cv::Mat firstFrame;
	DetectFaces facedetector;
	DetectEyes eyesdetector;
	DrawOnFace drawOnFace;
	DrawEnvironment drawEnvironment;

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

	int screenshotMessageTimer;
	std::string screenshotMessage;
	bool screenshotSaved;

	Mat showglassesOff;
	Mat showglassesOn;
	Mat showhatOff;
	Mat showhatOn;
	
	bool showglasses;
	bool showhat;

	bool environmentNo;
	bool environmentA;
	bool environmentB;
	bool environmentC;
	bool environmentD;
	Mat environmentNo_on;
	Mat environmentNo_off;
	Mat environmentA_on;
	Mat environmentA_off;
	Mat environmentB_on;
	Mat environmentB_off;
	Mat environmentC_on;
	Mat environmentC_off;
	Mat environmentD_on;
	Mat environmentD_off;
	
};
#endif