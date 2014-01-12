#ifndef DRAWENVIRONMENT_H__
#define DRAWENVIRONMENT_H__
#include <opencv2/opencv.hpp>

class DrawEnvironment{

public:
	DrawEnvironment(void);
	~DrawEnvironment(void);
	void drawEnvironment(cv::Mat& processedFrame);
private:
	void DrawEnvironment::overlayImage(cv::Mat& background, cv::Mat& overlay);
};
#endif