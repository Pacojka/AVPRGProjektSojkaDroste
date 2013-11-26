#ifndef _BACKGROUNDSUBSTRACTION_H
#define _BACKGROUNDSUBSTRACTION_H
#include "VideoEngine.h"
class Backgroundsubstraction: public VideoEngine
{
public:
	Backgroundsubstraction(void);
	~Backgroundsubstraction(void);
	virtual void showVideoFrame(const cv::Mat& videoFrame);
	virtual void processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame);
	virtual void showProcessedFrame(const cv::Mat&processedFrame);
private:
	cv::Mat firstFrame;
};
#endif