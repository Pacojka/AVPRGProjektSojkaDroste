#include "Backgroundsubstraction.h"
using namespace cv;

Backgroundsubstraction::Backgroundsubstraction(void){
	namedWindow("Video");
	namedWindow("Result");
}

Backgroundsubstraction::~Backgroundsubstraction(void){
	destroyAllWindows();
}
void Backgroundsubstraction::showVideoFrame(const cv::Mat& videoFrame){
	imshow("Video", videoFrame);
}
void Backgroundsubstraction::processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame){
	Mat grayFrame;
	cvtColor(videoFrame, grayFrame, CV_BGR2GRAY);
	if (frameNumber == 1){
		grayFrame.copyTo(firstFrame);
	}
	absdiff(grayFrame, firstFrame, grayFrame);
	threshold(grayFrame, grayFrame, 20, 255, THRESH_BINARY);
	
	processedFrame.create(frameHeight, frameWidth, CV_8UC3);
	processedFrame.setTo(Scalar(0,255,255), grayFrame);
	processedFrame.setTo(Scalar(255,255,0), 255-grayFrame);
}
void Backgroundsubstraction::showProcessedFrame(const cv::Mat&processedFrame){
	imshow("Result", processedFrame);
}
