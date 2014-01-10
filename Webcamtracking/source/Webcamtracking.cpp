#include "Webcamtracking.h"
#include "mousecallback.h"
#include <sstream>
using namespace cv;
Webcamtracking::Webcamtracking(void){
	debugDraw = true;
	overlayImages = false;
	detectEyes = false;
	flipImg = false;
	namedWindow("Video");
	namedWindow("Result");
	setMouseCallback("Result", mouseCallback1);
	//createButton("Brille", NULL); ???? - für button benutzen?
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
	//Auf Mausclick prüfen
	if(mouseLeftButtonUp){
		mouseLeftButtonUp = false;
		std::cout << "Maus geklickt an Position: (" << mouseClickPositionX << "," << mouseClickPositionY <<")" << std::endl;
	}
	
	/*
	//ausgabe größe der gesichter
	for (int i = 0; i < faces.size(); i++)
		{
			std::cout << std::endl << std::endl << "Groeße Gesicht:" << faces[i].height << "x" << faces[i].width << std::endl;
		}	

	*/

	if(detectEyes){
		//augenerkennung
		if(faces.size()>0){
			std::vector<cv::Rect> pairOfEyes;
			for (int i = 0; i < faces.size(); i++)
			{
				std::cout << "Groeße Gesicht:" << faces[i].height << "x" << faces[i].width << std::endl;
				eyesdetector.detect(processedFrame,faces[i],pairOfEyes);
				if(pairOfEyes.size() == 2)eyes.insert(eyes.end(), pairOfEyes.begin(), pairOfEyes.end());
			}
			//std::cout << eyes.size() << std::endl;
		}
	}

	if(overlayImages){
	//Bilder überlagern
		for (int i = 0; i < eyes.size(); i+=2)
        {
            Rect leftEye = eyes[i].x < eyes[i+1].x?eyes[i]:eyes[i+1];
			Rect rightEye = eyes[i].x < eyes[i+1].x?eyes[i+1]:eyes[i];
			drawOnFace.drawOnFace(processedFrame, faces[i/2], leftEye, rightEye);
        }
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

	//keyhandling
	char k = cvWaitKey(10);
	    switch(k){
      case 'd':
        debugDraw = debugDraw == true?false:true;
        break;
	  case 'D':
        debugDraw = debugDraw == true?false:true;
        break;
      case 'i':
        overlayImages = overlayImages == true?false:true;
        break;
      case 'I':
        overlayImages = overlayImages == true?false:true;
        break;
      case 'e':
        detectEyes = detectEyes == true?false:true;
        break;
      case 'E':
        detectEyes = detectEyes == true?false:true;
        break;
    }

	
	std::ostringstream os;
	os  << "(D)ebugDraw = " << (debugDraw == true?"true":"false");
	putText(processedFrame, os.str(), Point(5,15), FONT_HERSHEY_SIMPLEX, .4, debugDraw == true?Scalar(0, 255, 0):Scalar(0, 0, 255));
	os.str("");
	os.clear();
	os  << "Detect(E)yes = " << (detectEyes == true?"true":"false");
	putText(processedFrame, os.str(), Point(5,30), FONT_HERSHEY_SIMPLEX, .4, detectEyes == true?Scalar(0, 255, 0):Scalar(0, 0, 255));
	os.str("");
	os.clear();
	os  << "overlay(I)mages = " << (overlayImages == true?"true":"false");
	putText(processedFrame, os.str(), Point(5,45), FONT_HERSHEY_SIMPLEX, .4, overlayImages == true?Scalar(0, 255, 0):Scalar(0, 0, 255));
	os.str("");
	os.clear();
}
void Webcamtracking::showProcessedFrame(const cv::Mat&processedFrame){
	imshow("Result", processedFrame);
}

