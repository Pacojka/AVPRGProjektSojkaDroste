#ifndef _WEBCAMTRACKING_H
#define _WEBCAMTRACKING_H
#include "VideoEngine.h"
#include "DetectFaces.h"
#include "DetectEyes.h"
#include "DrawOnFace.h"

class Webcamtracking: public VideoEngine
{
public:
	Webcamtracking(void);
	~Webcamtracking(void);
	virtual void showVideoFrame(const cv::Mat& videoFrame);
	virtual void processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame);
	virtual void showProcessedFrame(const cv::Mat&processedFrame);
private:
	//cv::Mat firstFrame;
	DetectFaces facedetector;
	DetectEyes eyesdetector;
	DrawOnFace drawOnFace;

	bool debugDraw;
	bool flipImg;
};
#endif