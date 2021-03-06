#include "Webcamtracking.h"
#include "mousecallback.h"
#include <sstream>
using namespace cv;
Webcamtracking::Webcamtracking(void){
	debugDraw = false;
	overlayImages = true;
	detectEyes = true;	
	flipImg = false;
	rescaleButtons = true;
	namedWindow("Result");
	setMouseCallback("Result", mouseCallback1);

	screenshotMessageTimer = 0;
	screenshotMessage = "";
	showglasses = true;
	showhat = true;

	environmentNo = true;
	environmentA = false;
	environmentB = false;
	environmentC = false;
	environmentD = false;
	//Buttonbilder laden
	buttonHeight = 0;
	buttonWidth = 0;
	buttonAnz = 5;
	
	changeglasses = imread("img\\changeglasses.jpg", -1);
	changehat = imread("img\\changehat.jpg", -1);
	showglassesOff = imread("img\\showglasses_off.jpg", -1);
	showglassesOn = imread("img\\showglasses_on.jpg", -1);
	showhatOff = imread("img\\showhat_off.jpg", -1);
	showhatOn = imread("img\\showhat_on.jpg", -1);
	environmentNo_on = imread("img\\noenvironment_on.jpg", -1);
	environmentNo_off = imread("img\\noenvironment_off.jpg", -1);
	environmentA_on = imread("img\\environmentA_on.jpg", -1);
	environmentA_off = imread("img\\environmentA_off.jpg", -1);
	environmentB_on = imread("img\\environmentB_on.jpg", -1);
	environmentB_off = imread("img\\environmentB_off.jpg", -1);
	environmentC_on = imread("img\\environmentC_on.jpg", -1);
	environmentC_off = imread("img\\environmentC_off.jpg", -1);
	environmentD_on = imread("img\\environmentD_on.jpg", -1);
	environmentD_off = imread("img\\environmentD_off.jpg", -1);
	
	screenshot = imread("img//screenshot.jpg", -1);
}

Webcamtracking::~Webcamtracking(void){
	destroyAllWindows();
}
void Webcamtracking::calcAssetssize(const cv::Mat& videoFrame){
	//Buttons skalieren sobald videoFrame verf�gbar ist
	if(rescaleButtons){
		drawEnvironment.initialize(videoFrame.size().width, videoFrame.size().height);
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
		
		resize(environmentNo_on, environmentNo_on, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(environmentNo_off, environmentNo_off, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(environmentA_on, environmentA_on, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(environmentA_off, environmentA_off, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(environmentB_on, environmentB_on, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(environmentB_off, environmentB_off, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(environmentC_on, environmentC_on, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(environmentC_off, environmentC_off, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(environmentD_on, environmentD_on, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		resize(environmentD_off, environmentD_off, Size(), scaleFactor, scaleFactor,INTER_LINEAR);
		
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
	
	if(detectEyes){
		//augenerkennung
		if(faces.size()>0){
			for (int i = 0; i < faces.size(); i++)
			{
				std::vector<cv::Rect> pairOfEyes;
				eyesdetector.detect(frameCopy,faces[i],pairOfEyes);
				if(pairOfEyes.size() == 2){
					eyes.insert(eyes.end(),pairOfEyes.begin(), pairOfEyes.end());
					if(overlayImages){
					//Bilder �berlagern
						Rect leftEye = pairOfEyes[0].x < pairOfEyes[1].x?pairOfEyes[0]:pairOfEyes[1];
						Rect rightEye = pairOfEyes[1].x < pairOfEyes[0].x?pairOfEyes[0]:pairOfEyes[1];
						drawOnFace.drawOnFace(frameCopy, faces[i], leftEye, rightEye, showhat, showglasses);
					}
				}
			}
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
      case 'Q':
        //
        break;
      case 'q':
        //
		break;
    }

	if(debugDraw){
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
	}
	
	//AusgabeFrame Vorbereiten
	if(environmentNo == false && (environmentA || environmentB || environmentC || environmentD)){
		int envnumber;
		if(environmentA)envnumber = 1;
		else if(environmentB)envnumber = 2;
		else if(environmentC)envnumber = 3;
		else if(environmentD)envnumber = 4;

		drawEnvironment.drawEnvironment(frameCopy,envnumber);
	}
	
	processedFrame = Mat(frameCopy.rows+buttonHeight*2, frameCopy.cols, frameCopy.type());
	frameCopy.copyTo(processedFrame(Rect(Point(0,buttonHeight),frameCopy.size())));

	
	//Buttons Zeichen und pr�fen ob sie angeklickt wurden
	Point position;
	//obere ButtonLeiste
	//Button #1 changeGlasses
	position = Point(0*buttonWidth,0);

	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			drawOnFace.toggleGlasses();
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
			drawOnFace.toggleHat();
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
			//Bild Speichern
			String name = "Screenshots\\Screenshot";
			int number = 1;
			bool nichtfertig = true;
			String filename;
			while(nichtfertig){
				std::stringstream ss;
				ss << name << number << ".jpg";
				filename = ss.str();
				Mat imagedummy = imread(filename);
				if(imagedummy.empty())nichtfertig = false;
				else number ++;
			}
			screenshotMessageTimer = 45;
			screenshotSaved = imwrite(filename, frameCopy);
			if(screenshotSaved){
				screenshotMessage = "Screenshot erfolgreich aufgezeichnet.";
			}else{
				screenshotMessage = "Screenshot konnte nicht erstellt werden.";

			}
		}
	}
	//Richtigen Button zeichnen
	screenshot.copyTo(processedFrame(Rect(position,screenshot.size())));
	
	//Untere Buttonleiste

	//Button #6 noEnvironment
	position = Point(0*buttonWidth,processedFrame.size().height-buttonHeight);

	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			if(!environmentNo){
				environmentNo = true;
				environmentA = false;
				environmentB = false;
				environmentC = false;
				environmentD = false;
			}
		}
	}
	//Richtigen Button zeichnen
	if(environmentNo)environmentNo_on.copyTo(processedFrame(Rect(position,environmentNo_on.size())));
	else environmentNo_off.copyTo(processedFrame(Rect(position,environmentNo_off.size())));

	//Button #7 EnvironmentA
	position = Point(1*buttonWidth,processedFrame.size().height-buttonHeight);

	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			if(!environmentA){
				environmentNo = false;
				environmentA = true;
				environmentB = false;
				environmentC = false;
				environmentD = false;
			}
		}
	}
	//Richtigen Button zeichnen
	if(environmentA)environmentA_on.copyTo(processedFrame(Rect(position,environmentA_on.size())));
	else environmentA_off.copyTo(processedFrame(Rect(position,environmentA_off.size())));

	//Button #8 EnvironmentB
	position = Point(2*buttonWidth,processedFrame.size().height-buttonHeight);

	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			if(!environmentB){
				environmentNo = false;
				environmentA = false;
				environmentB = true;
				environmentC = false;
				environmentD = false;
			}
		}
	}
	//Richtigen Button zeichnen
	if(environmentB)environmentB_on.copyTo(processedFrame(Rect(position,environmentB_on.size())));
	else environmentB_off.copyTo(processedFrame(Rect(position,environmentB_off.size())));

	//Button #9 EnvironmentC
	position = Point(3*buttonWidth,processedFrame.size().height-buttonHeight);

	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			if(!environmentC){
				environmentNo = false;
				environmentA = false;
				environmentB = false;
				environmentC = true;
				environmentD = false;
			}
		}
	}
	//Richtigen Button zeichnen
	if(environmentC)environmentC_on.copyTo(processedFrame(Rect(position,environmentC_on.size())));
	else environmentC_off.copyTo(processedFrame(Rect(position,environmentC_off.size())));

	//Button #10 EnvironmentD
	position = Point(4*buttonWidth,processedFrame.size().height-buttonHeight);

	//Klick auswerten
	if(mouseLeftButtonUp){
		if(mouseClickPositionX >=position.x && mouseClickPositionX <= position.x+buttonWidth
			&& mouseClickPositionY >=position.y && mouseClickPositionY <= position.y+buttonHeight){
			mouseLeftButtonUp = false;
			if(!environmentD){
				environmentNo = false;
				environmentA = false;
				environmentB = false;
				environmentC = false;
				environmentD = true;
			}
		}
	}
	//Richtigen Button zeichnen
	if(environmentD)environmentD_on.copyTo(processedFrame(Rect(position,environmentD_on.size())));
	else environmentD_off.copyTo(processedFrame(Rect(position,environmentD_off.size())));

	//wenn screenshot aufgezeichnet wurde Nachricht einblenden
	if(screenshotMessageTimer > 0){
		screenshotMessageTimer--;

		std::ostringstream os;
		os  << screenshotMessage;
		putText(processedFrame, os.str(), Point(15,processedFrame.size().height-15-buttonHeight), FONT_HERSHEY_DUPLEX, .8, screenshotSaved == true?Scalar(0, 255, 0):Scalar(0, 0, 255));
	}
}
void Webcamtracking::showProcessedFrame(const cv::Mat&processedFrame){
	imshow("Result", processedFrame);
}