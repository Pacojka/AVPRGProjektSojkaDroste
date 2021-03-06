#include "DetectEyes.h"
using namespace cv;

DetectEyes::DetectEyes(){
	//PFAD MUSS ANGEPASST WERDEN :D
	eye_cascade = CascadeClassifier("data\\haarcascade_eye.xml");
	//eye_cascade = CascadeClassifier("haarcascade_eye_tree_eyeglasses.xml");

}
DetectEyes::~DetectEyes(){}
void DetectEyes::detect(cv::Mat& videoFrame, cv::Rect& faceRect, std::vector<cv::Rect>& eyes){
	//Profile laden
	Mat face = videoFrame(faceRect);
	Mat grayFrame;
	cvtColor(face, grayFrame, CV_BGR2GRAY);
	eye_cascade.detectMultiScale(grayFrame, eyes, 1.1, 3, 3, Size(face.size().width/8,face.size().width/8), Size(face.size().width/4,face.size().width/4));
	
	for (int i = 0; i < eyes.size(); i++)
        {
			eyes[i].x = eyes[i].x + faceRect.x;
			eyes[i].y = eyes[i].y + faceRect.y;
        }
}
