#include "findEyeRanzig.h"
using namespace cv;

void findEye(cv::Mat& videoFrame, cv::Point& eyePoint){
	Mat hsvFrame;
	Mat processedFrame;

	vector<Mat> hsvPlanes;
	vector<Mat> hsvEyePlanes;
	cvtColor(videoFrame, hsvFrame, CV_BGR2HSV);
	split(hsvFrame, hsvPlanes);

	//if (frameNumber == 1){
	//	hsvFrame.copyTo(firstFrame);
	//}
	//absdiff(hsvFrame, firstFrame, hsvFrame);
	//threshold(hsvFrame, hsvFrame, 20, 255, THRESH_BINARY);
	
	processedFrame.create(videoFrame.size().height, videoFrame.size().width, hsvPlanes[0].type());
	//processedFrame.setTo(Scalar(0,255,255), hsvFrame);
	//processedFrame.setTo(Scalar(255,255,0), 255-hsvFrame);
	Mat processedFrame2;
	Mat processedFrame3;
	hsvPlanes[0].copyTo(processedFrame);
	hsvPlanes[1].copyTo(processedFrame2);
	hsvPlanes[2].copyTo(processedFrame3);
	
	//Mat testAuge = imread("D:\\Studium\\HAW\\WS2013-2014\\AudioVideoPRG\\Projekt\\auge.png");
	Mat testAuge = imread("D:\\Studium\\HAW\\WS2013-2014\\AudioVideoPRG\\Projekt\\augeSATURATION.png");
	split(testAuge, hsvEyePlanes);

	Mat result;
	matchTemplate(processedFrame2, hsvEyePlanes[1], result, 3);
	Mat mask;
	minMaxLoc(result, NULL, NULL, NULL, &eyePoint, mask);
}
