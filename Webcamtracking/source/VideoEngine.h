#ifndef __VIDEOENGINE_H
#define __VIDEOENGINE_H
#include <opencv2/opencv.hpp>
#include <string>


class VideoEngine
{
public:
	VideoEngine();
	virtual ~VideoEngine(void);
	bool open();
	void run();
	virtual void calcAssetssize(const cv::Mat& videoFrame);
	virtual void processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame);
	virtual void showProcessedFrame(const cv::Mat&processedFrame);
protected:
	cv::VideoCapture videoCapture;
	int frameWidth;
	int frameHeight;
	int frameNumber;
};
#endif