#include "Webcamtracking.h"
#include <sstream>
using namespace cv;
Webcamtracking::Webcamtracking(void){
	debugDraw = true;
	flipImg = false;
	namedWindow("Video");
	namedWindow("Result");
	//createButton("Brille", NULL); ???? - f�r button benutzen?
}

Webcamtracking::~Webcamtracking(void){
	destroyAllWindows();
}
void Webcamtracking::showVideoFrame(const cv::Mat& videoFrame){
	imshow("Video", videoFrame);
}

void Webcamtracking::processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame){
	//Lokale Variablen
	Mat test;
	std::vector<cv::Rect> faces;
	std::vector<cv::Rect> eyes;

	videoFrame.copyTo(processedFrame);

	//Webcamflip
	if(flipImg == true)
	cv::flip(processedFrame, processedFrame, 0);
	//gesichtserkennung
	facedetector.detect(processedFrame, faces);
	
	
	//augenerkennung
	if(faces.size()>0){
		std::vector<cv::Rect> pairOfEyes;
		for (int i = 0; i < faces.size(); i++)
        {
			eyesdetector.detect(processedFrame,faces[i],pairOfEyes);
			if(pairOfEyes.size() == 2)eyes.insert(eyes.end(), pairOfEyes.begin(), pairOfEyes.end());
		}
		std::cout << eyes.size() << std::endl;
	}
	
	//brillen aufsetzen
		for (int i = 0; i < eyes.size(); i+=2)
        {
            Rect leftEye = eyes[i].x < eyes[i+1].x?eyes[i]:eyes[i+1];
			Rect rightEye = eyes[i].x < eyes[i+1].x?eyes[i+1]:eyes[i];
			drawOnFace.drawOnFace(processedFrame, faces[i/2], leftEye, rightEye);
        }
	//Debug rects zeichnen
		if(debugDraw){
			for (int i = 0; i < faces.size(); i++)
				{
					rectangle(processedFrame, faces[i], Scalar(0,255,0));
				}
			for (int i = 0; i < eyes.size(); i++)
				{
					rectangle(processedFrame, eyes[i], Scalar(0,0,255));
				}		
		}
	
	char k;
	k=cvWaitKey(10);
	if(k == 100){
		debugDraw = debugDraw == true?false:true;
	}

	std::ostringstream os;
	os  << "DebugDraw = " << (debugDraw == true?"true":"false");
	putText(processedFrame, os.str(), Point(10,15), FONT_HERSHEY_SIMPLEX, .5, debugDraw == true?Scalar(0, 255, 0):Scalar(0, 0, 255));
		

}
void Webcamtracking::showProcessedFrame(const cv::Mat&processedFrame){
	imshow("Result", processedFrame);
}

