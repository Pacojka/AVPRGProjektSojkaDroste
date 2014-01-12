#ifndef DRAWENVIRONMENT_H__
#define DRAWENVIRONMENT_H__
#include <opencv2/opencv.hpp>

class DrawEnvironment{

public:
	DrawEnvironment(void);
	~DrawEnvironment(void);
	void drawEnvironment(cv::Mat& processedFrame, int number);
	void initialize(int width, int height);
private:
	cv::Mat environment1;
	cv::Mat environment2;
	cv::Mat environment3;
	cv::Mat environment4;
	int environmentWidth;
	int environmentHeight;
	double environmentScaleWidth;
	double environmentScaleHeight;
	cv::Rect env1_ROI;
	cv::Rect env2_ROI;
	cv::Rect env3_ROI;
	cv::Rect env4_ROI;
	cv::Size env1_size;
	cv::Size env2_size;
	cv::Size env3_size;
	cv::Size env4_size;
};
#endif