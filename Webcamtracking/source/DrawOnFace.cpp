#include "DrawOnFace.h"
#include <math.h>
using namespace cv;

DrawOnFace::DrawOnFace(){}
DrawOnFace::~DrawOnFace(){}


void overlayImage(Mat &background, Mat &overlay)
{
	int cut = overlay.size().height-background.size().height;
	for(int y = 0; y < background.rows; y++){
		for(int x = 0; x < background.cols; x++){
			//Opacity ("Durchsichtigkeit") des aktuelles Pixels berechnen -> (Alphakanal / 255) = [0-1]
				double opacity = ((double)overlay.data[(y+cut) * overlay.step + x * overlay.channels() + 3]) / 255.f;
					//Fuer jeden Channel einzeln die Opacity setzen
						for(int c = 0; opacity > 0 && c < background.channels(); c++)
						{
						//ovPx = aktueller (Uchar-)Wert des Overlaybildes
							uchar ovPx = overlay.data[(y+cut) * overlay.step + x * overlay.channels() + c];
						//bgPx = aktueller (Uchar-)Wert des Hintergrundbildes
							uchar bgPx = background.data[y * background.step + x * background.channels() + c];
						//Übereinanderlegen der beiden Werte
							background.data[y*background.step + background.channels()*x + c] = bgPx * (1.-opacity) + ovPx * opacity;
						}
				//delete &opacity;
		}
	}
	
}

void DrawOnFace::drawOnFace(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect){
	//Schwarzes Rechteck zu Debugzwecken zeichnen
	    
		//rectangle(resultFrame, Rect(leftEyeRect.x,leftEyeRect.y, rightEyeRect.x+rightEyeRect.width-leftEyeRect.x, rightEyeRect.y+rightEyeRect.height-leftEyeRect.y), Scalar(0,0,0));

	//Mat für Brille initialisieren (inkl. Alphakanal)
		Mat glasses = imread("brille.png", -1);
	
	//Rotationswinkel des Gesichtes/der Augen berechnen
		//Ankathete
		Point2f a = Point2f((leftEyeRect.x+leftEyeRect.size().width/2.f),(leftEyeRect.y+leftEyeRect.size().height/2.f));
		Point2f b = Point2f((rightEyeRect.x+rightEyeRect.size().width/2.f),(rightEyeRect.y+rightEyeRect.size().height/2.f));
		Point2f c = Point2f(b.x,a.y);

		double aside = (b.x-a.x);
		double bside = (a.y-b.y);
		double cside = sqrt(aside*aside+bside*bside);
		double rota = -asin(bside/cside)*180/3.1415f;

		Mat faceRect_temp; 
		resultFrame(faceRect).copyTo(faceRect_temp);
		namedWindow("GET REKT");
		
		Point2f rotPt(((a.x+b.x)/2.f)-faceRect.x,((a.y+b.y)/2.f)-faceRect.y);
		Mat rotMat = getRotationMatrix2D(rotPt, rota, 1.0);
		warpAffine(faceRect_temp, faceRect_temp, rotMat, faceRect_temp.size());
		

		

	//Brillengröße=(Brillenabstand/Augenabstand)
		float scaleFactor = ((float) glasses.cols / ((rightEyeRect.x+rightEyeRect.width) - leftEyeRect.x));

	//Brillengröße dem Skalierungsfaktor entsprechend verändern
		resize(glasses, glasses, Size(), (1.f/scaleFactor), (1.f/scaleFactor),INTER_LINEAR);


		Point2f roiPt((((a.x+b.x)/2.f)-faceRect.x)-glasses.size().width/2.f,((a.y+b.y)/2.f)-faceRect.y-glasses.size().height/2.f);
		Mat glassesROI_temp = faceRect_temp(Rect(roiPt, glasses.size()));
		overlayImage(glassesROI_temp, glasses);
		imshow("GET REKT", faceRect_temp);
		rotMat = getRotationMatrix2D(rotPt, -rota, 1.0);
		warpAffine(faceRect_temp, faceRect_temp, rotMat, faceRect_temp.size());

		std::cout << "hehejo " << std::endl;

		float glassDiag = sqrtf(glasses.size().width*glasses.size().width+glasses.size().height*glasses.size().height);

		glassesROI_temp = faceRect_temp(
			Rect(Point2f(rotPt.x-glassDiag/2.f,rotPt.y-glasses.size().height/2.f-abs(bside)),
			Size(glassDiag,
			glasses.size().height+(abs(bside)*2))));
		
		/*namedWindow("AUSGABE");
		circle(resultFrame, a, 3, Scalar(255,255,255), 1);
		circle(resultFrame, b, 3, Scalar(255,255,255), 1);
		circle(resultFrame, c, 3, Scalar(255,255,255), 1);
		imshow("AUSGABE", glassesROI_temp);*/
		

		rotPt = Point(rotPt.x+faceRect.x,rotPt.y+faceRect.y);
		Mat glassesROI = resultFrame(Rect(Point2f(rotPt.x-glassDiag/2.f,rotPt.y-glasses.size().height/2.f-abs(bside)),
			Size(glassDiag,
			glasses.size().height+(abs(bside)*2))));

		glassesROI_temp.copyTo(glassesROI);

	//HUT
	//Mat für Hut initialisieren (inkl. Alphakanal)
		Mat hat = imread("hut.png", -1);

		
		resize(hat, hat, Size(), 4.f/scaleFactor, 4.f/scaleFactor, INTER_LINEAR);

		int hatHeight = 1;
		if(faceRect.y-100 <= 0) hatHeight = hat.size().height+faceRect.y-100; else hatHeight=hat.size().height;

		//cout << endl << "1 hatHeight: " << hatHeight << endl;

		//Mat hatROI = resultFrame(Rect(faceRect.x+50,max(faceRect.y-100,0),hat.size().width,hatHeight));
		Mat hatROI = resultFrame(Rect(leftEyeRect.x,max((leftEyeRect.y-((rightEyeRect.x+rightEyeRect.width) - leftEyeRect.x))-(hat.size().height/3),0),hat.size().width,hatHeight));

		overlayImage(hatROI, hat);
				
		
}
