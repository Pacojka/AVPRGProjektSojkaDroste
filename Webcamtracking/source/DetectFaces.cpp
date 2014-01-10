#include "DetectFaces.h"
using namespace cv;

DetectFaces::DetectFaces(){
	//PFAD MUSS ANGEPASST WERDEN :D
	face_cascade = CascadeClassifier("haarcascade_frontalface_default.xml");

}
DetectFaces::~DetectFaces(){}
void DetectFaces::detect(cv::Mat& videoFrame, std::vector<cv::Rect>& faces){
	//Profile laden
	Mat grayFrame;
	cvtColor(videoFrame, grayFrame, CV_BGR2GRAY);
	face_cascade.detectMultiScale(grayFrame, faces, 1.99, 4, 3, Size(grayFrame.size().width/4,grayFrame.size().width/4), Size(grayFrame.size().width/3,grayFrame.size().width/3));
}
/*
During these parameters, you need to pay more attention to four of them:
scaleFactor – Parameter specifying how much the image size is reduced at each image scale.
Basically the scale factor is used to create your scale pyramid. More explanation can be found here. 1.05 is a good possible value for this, which means you use a small step for resizing, i.e. reduce size by 5 %, you increase the chance of a matching size with the model for detection is found.
minNeighbors – Parameter specifying how many neighbors each candidate rectangle should have to retain it.
This parameter will affect the quality of the detected faces. Higher value results in less detections but with higher quality. 3~6 is a good value for it.
minSize – Minimum possible object size. Objects smaller than that are ignored.
This parameter determine how small size you want to detect. You decide it! Usually, [30, 30] is a good start for face detections.
maxSize – Maximum possible object size. Objects bigger than that are ignored.
This parameter determine how big size you want to detect. Again, you decide it! Usually, you don't need to set it manually, which means you want to detect any big, i.e. don't want to miss any one that is big enough.
*/