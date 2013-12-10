#include "DetectFaces.h"
using namespace cv;

DetectFaces::DetectFaces(){
	//PFADMUSS ANGEPASST WERDEN :D
	face_cascade = CascadeClassifier("C:\\OpenCV2.4.2\\opencv\\data\\haarcascades\\haarcascade_frontalface_default.xml");

}
DetectFaces::~DetectFaces(){}
void DetectFaces::detect(cv::Mat& videoFrame, std::vector<cv::Rect>& faces){
	//Profile laden
	Mat grayFrame;
	cvtColor(videoFrame, grayFrame, CV_BGR2GRAY);
	face_cascade.detectMultiScale(grayFrame, faces, 3, 3, 0, Size(), Size());
}