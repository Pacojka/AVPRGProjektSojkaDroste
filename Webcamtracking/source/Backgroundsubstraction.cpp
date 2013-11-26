#include "Backgroundsubstraction.h"
using namespace cv;

Backgroundsubstraction::Backgroundsubstraction(void){
	namedWindow("Video");
	namedWindow("Result");
	namedWindow("Saturation");
	namedWindow("Value");
}

Backgroundsubstraction::~Backgroundsubstraction(void){
	destroyAllWindows();
}
void Backgroundsubstraction::showVideoFrame(const cv::Mat& videoFrame){
	imshow("Video", videoFrame);
}

/*Point findMax(Mat* mat){

    double value;

    double maxVal = 0;

    Point max;

    for (int row = 0; row < mat->rows; row++) {

        for (int col = 0; col < mat->cols; col++) {

            value = cvGetReal2D(mat, row, col);

            if (value > maxVal) {

                maxVal = value;

                max.x = col;

                max.y = row;

                

            }

        }

    }

    return max;

}
*/
void Backgroundsubstraction::processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame){
	Mat hsvFrame;
	vector<Mat> hsvPlanes;
	cvtColor(videoFrame, hsvFrame, CV_BGR2HSV);
	split(hsvFrame, hsvPlanes);

	if (frameNumber == 1){
		hsvFrame.copyTo(firstFrame);
	}
	//absdiff(hsvFrame, firstFrame, hsvFrame);
	//threshold(hsvFrame, hsvFrame, 20, 255, THRESH_BINARY);
	
	processedFrame.create(frameHeight, frameWidth, hsvPlanes[0].type());
	//processedFrame.setTo(Scalar(0,255,255), hsvFrame);
	//processedFrame.setTo(Scalar(255,255,0), 255-hsvFrame);
	Mat processedFrame2;
	Mat processedFrame3;
	hsvPlanes[0].copyTo(processedFrame);
	hsvPlanes[1].copyTo(processedFrame2);
	hsvPlanes[2].copyTo(processedFrame3);
	
	Mat testAuge = imread("C:\\Users\\User\\Pictures\\testauge.png");
	Mat result;
	matchTemplate(videoFrame, testAuge, result, 3);
	Point augensohn; 
	Mat mask;

	minMaxLoc(result, NULL, NULL, NULL, &augensohn, mask);

	line(processedFrame2,augensohn, Point(0,0), Scalar(255,255,0), 1);

	imshow("Saturation", processedFrame2);	 
	imshow("Value", processedFrame3);


}
void Backgroundsubstraction::showProcessedFrame(const cv::Mat&processedFrame){
	imshow("Result", processedFrame);
}

