#include "Webcamtracking.h"
#include "findEyeRanzig.h"

using namespace cv;

Webcamtracking::Webcamtracking(void){
	namedWindow("Video");
	namedWindow("Result");
}

Webcamtracking::~Webcamtracking(void){
	destroyAllWindows();
}
void Webcamtracking::showVideoFrame(const cv::Mat& videoFrame){
	imshow("Video", videoFrame);
}

void Webcamtracking::processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame){
	//Lokale Variablen
	Point augensohn;
	augensohn = Point(10,10);
	

	Mat test;
	videoFrame.copyTo(test);
	findEye(test, augensohn);


	videoFrame.copyTo(processedFrame);
	line(processedFrame,augensohn, Point(0,0), Scalar(255,255,0), 1);
}
void Webcamtracking::showProcessedFrame(const cv::Mat&processedFrame){
	imshow("Result", processedFrame);
}

