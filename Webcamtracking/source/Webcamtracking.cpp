#include "Webcamtracking.h"


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
	Mat test;
	std::vector<cv::Rect> faces;

	videoFrame.copyTo(processedFrame);
	//gesichtserkennung
	facedetector.detect(processedFrame, faces);
	
	//rects zeichnen
    for (int i = 0; i < faces.size(); i++)
        {
            rectangle(processedFrame, faces[i], Scalar(0,255,0));
        }
}
void Webcamtracking::showProcessedFrame(const cv::Mat&processedFrame){
	imshow("Result", processedFrame);
}

