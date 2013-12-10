#ifndef DETECTEYES_H__
#define DETECTEYES_H__
#include <opencv2/opencv.hpp>

class DetectEyes
{
public:
	DetectEyes(void);
	~DetectEyes(void);
	void detect(cv::Mat& videoFrame, cv::Rect& faceRect, std::vector<cv::Rect>& eyes);
private:
	cv::CascadeClassifier eye_cascade;
};
#endif