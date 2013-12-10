#ifndef DETECTFACES_H__
#define DETECTFACES_H__
#include <opencv2/opencv.hpp>

class DetectFaces
{
public:
	DetectFaces(void);
	~DetectFaces(void);
	void detect(cv::Mat& videoFrame, std::vector<cv::Rect>& faces);
private:
	cv::CascadeClassifier face_cascade;
};
#endif