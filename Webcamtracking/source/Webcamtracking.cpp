#include "Webcamtracking.h"
#include "mousecallback.h"
#include <sstream>
using namespace cv;
Webcamtracking::Webcamtracking(void){
	debugDraw = true;
	overlayImages = false;
	detectEyes = false;
	flipImg = false;
	rescaleButtons = true;
	namedWindow("Video");
	namedWindow("Result");
	setMouseCallback("Result", mouseCallback1);

	showglasses = true;
	showhat = true;
	//Buttonbilder laden
	buttonHeight = 0;
	buttonWidth = 0;
	buttonAnz = 5;
	changeglasses = imread("changeglasses.jpg", -1);
	changehat = imread("changehat.jpg", -1);
	showglassesOff = imread("showglasses_off.jpg", -1);
	showglassesOn = imread("showglasses_on.jpg", -1);
	showhatOff = imread("showhat_off.jpg", -1);
	showhatOn = imread("showhat_on.jpg", -1);
	
	screenshot = imread("screenshot.jpg", -1);
}

Webcamtracking::~Webcamtracking(void){
	destroyAllWindows();
}
void Webcamtracking::showVideoFrame(const cv::Mat& videoFrame){
	imshow("Video", videoFrame);
	//Buttons skalieren sobald videoFrame verfügbar ist
	if(rescaleButtons){
		rescaleButtons = false;
		double buttonWidthDummy = (double) videoFrame.size().width/buttonAnz;
		double scaleFactor = buttonWidthDummy * (1.f/changeglasses.size().width);

		
		resize(changeglasses, changeglasses, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(changehat, changehat, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(showglassesOff, showglassesOff, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(showglassesOn, showglassesOn, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(showhatOff, showhatOff, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(showhatOn, showhatOn, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(screenshot, screenshot, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		buttonHeight = screenshot.size().height;
		buttonWidth = screenshot.size().width;
	}
}

void Webcamtracking::processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame){
	//Lokale Variablen
	Mat frameCopy;
	std::vector<cv::Rect> faces;
	std::vector<cv::Rect> eyes;

	videoFrame.copyTo(frameCopy);

	//Webcamflip
	if(flipImg == true)
	cv::flip(frameCopy, frameCopy, 0);
	//gesichtserkennung
	facedetector.detect(frameCopy, faces);
	
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
				eyesdetector.detect(frameCopy,faces[i],pairOfEyes);
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
			drawOnFace.drawOnFace(frameCopy, faces[i/2], leftEye, rightEye);
        }
	}
	//Debug rects zeichnen
		if(debugDraw){
			for (int i = 0; i < faces.size(); i++)
				{
					rectangle(frameCopy, faces[i], Scalar(0,255,0));
				}
			for (int i = 0; i < eyes.size(); i++)
				{
					rectangle(frameCopy, eyes[i], Scalar(0,0,255));
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
	putText(frameCopy, os.str(), Point(5,15), FONT_HERSHEY_SIMPLEX, .4, debugDraw == true?Scalar(0, 255, 0):Scalar(0, 0, 255));
	os.str("");
	os.clear();
	os  << "Detect(E)yes = " << (detectEyes == true?"true":"false");
	putText(frameCopy, os.str(), Point(5,30), FONT_HERSHEY_SIMPLEX, .4, detectEyes == true?Scalar(0, 255, 0):Scalar(0, 0, 255));
	os.str("");
	os.clear();
	os  << "overlay(I)mages = " << (overlayImages == true?"true":"false");
	putText(frameCopy, os.str(), Point(5,45), FONT_HERSHEY_SIMPLEX, .4, overlayImages == true?Scalar(0, 255, 0):Scalar(0, 0, 255));
	os.str("");
	os.clear();

	//AusgabeFrame Vorbereiten
	
	processedFrame = Mat(frameCopy.rows+buttonHeight, frameCopy.cols, frameCopy.type());
	frameCopy.copyTo(processedFrame(Rect(Point(0,buttonHeight),frameCopy.size())));

	
	//Buttons Zeichen und prüfen ob sie angeklickt wurden
	Point position;

	//Button #1 changeGlasses
	position = Point(0*buttonWidth,0);

	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			std::cout << "changeglasses an Position: (" << mouseClickPositionX << "," << mouseClickPositionY <<")" << std::endl;
		}
	}
	//Richtigen Button zeichnen
	changeglasses.copyTo(processedFrame(Rect(position,changeglasses.size())));

	//Button #2 showGlasses
	position = Point(1*buttonWidth,0);
	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			showglasses = showglasses==true?false:true;
			std::cout << "Showglasses geklickt an Position: (" << mouseClickPositionX << "," << mouseClickPositionY <<")" << std::endl;
		}
	}
	//Richtigen Button zeichnen
	if(showglasses)showglassesOn.copyTo(processedFrame(Rect(position,showglassesOn.size())));
	else showglassesOff.copyTo(processedFrame(Rect(position,showglassesOn.size())));

	//Button #3 changeHat
	position = Point(2*buttonWidth,0);
	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			std::cout << "changeHat geklickt an Position: (" << mouseClickPositionX << "," << mouseClickPositionY <<")" << std::endl;
		}
	}
	//Richtigen Button zeichnen
	changehat.copyTo(processedFrame(Rect(position,changehat.size())));
	
	//Button #4 showHat
	position = Point(3*buttonWidth,0);
	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			showhat = showhat==true?false:true;
			std::cout << "Showhat geklickt an Position: (" << mouseClickPositionX << "," << mouseClickPositionY <<")" << std::endl;
		}
	}
	//Richtigen Button zeichnen
	if(showhat)showhatOn.copyTo(processedFrame(Rect(position,showhatOn.size())));
	else showhatOff.copyTo(processedFrame(Rect(position,showhatOff.size())));

	//Button #5 screenshot
	position = Point(4*buttonWidth,0);
	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			std::cout << "screenshot geklickt an Position: (" << mouseClickPositionX << "," << mouseClickPositionY <<")" << std::endl;
		}
	}
	//Richtigen Button zeichnen
	screenshot.copyTo(processedFrame(Rect(position,screenshot.size())));
	
}
void Webcamtracking::showProcessedFrame(const cv::Mat&processedFrame){
	imshow("Result", processedFrame);
}

