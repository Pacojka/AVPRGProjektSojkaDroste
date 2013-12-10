#ifndef DRAWONFACE_H__
#define DRAWONFACE_H__
#include <opencv2/opencv.hpp>

class DrawOnFace
{
public:
	DrawOnFace(void);
	~DrawOnFace(void);
	void drawOnFace(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect);
};
#endif