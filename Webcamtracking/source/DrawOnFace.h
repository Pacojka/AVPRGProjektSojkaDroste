#ifndef DRAWONFACE_H__
#define DRAWONFACE_H__
#include <opencv2/opencv.hpp>

class DrawOnFace
{
public:
	DrawOnFace(void);
	~DrawOnFace(void);
	void drawOnFace(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect, bool showHat, bool showGlasses);
private:
	cv::Mat glassesImg;
	cv::Mat hatImg;
	void overlayImage(cv::Mat &background, cv::Mat &overlay);
	void drawGlasses(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect);
	void drawHat(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect);
	float scaleFactor;
};

#endif