#ifndef DRAWONFACE_H__
#define DRAWONFACE_H__
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class DrawOnFace
{
public:
	DrawOnFace(void);
	~DrawOnFace(void);
	void drawOnFace(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect, bool showHat, bool showGlasses);
	void DrawOnFace::toggleHat();
	void DrawOnFace::toggleGlasses();
private:
	cv::Mat glassesImg;
	cv::Mat hatImg;
	void drawGlasses(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect);
	void drawHat(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect);
	float scaleFactor;
	int hatIndex;
	int glassesIndex;
};


#endif