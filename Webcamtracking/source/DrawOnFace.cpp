#include "DrawOnFace.h"
using namespace cv;

DrawOnFace::DrawOnFace(){}
DrawOnFace::~DrawOnFace(){}
void DrawOnFace::drawOnFace(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect){
	rectangle(resultFrame, Rect(leftEyeRect.x,leftEyeRect.y, rightEyeRect.x+rightEyeRect.width-leftEyeRect.x, rightEyeRect.y+rightEyeRect.height-leftEyeRect.y), Scalar(0,0,0));
}
