#include "DrawOnFace.h"
#include <math.h>
using namespace cv;

DrawOnFace::DrawOnFace(){

glassesImg = imread("brille.png", -1);
hatImg = imread("hut.png", -1);
float scaleFactor;

}
DrawOnFace::~DrawOnFace(){}


void DrawOnFace::overlayImage(Mat &background, Mat &overlay)
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
		}
	}
	
}

void DrawOnFace::drawOnFace(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect, bool showHat, bool showGlasses){
		
	if(showGlasses)drawGlasses(resultFrame, faceRect, leftEyeRect, rightEyeRect);
	if(showHat)drawHat(resultFrame, faceRect, leftEyeRect, rightEyeRect);

}

void DrawOnFace::drawGlasses(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect){
	//Mat für Brille initialisieren
		Mat glasses;
		glassesImg.copyTo(glasses);

	//Brillengröße=(Brillenabstand/Augenabstand) errechnen
		scaleFactor = ((float) glasses.cols / ((rightEyeRect.x+rightEyeRect.width) - leftEyeRect.x));

	//Brillengröße dem Skalierungsfaktor entsprechend verändern
		resize(glasses, glasses, Size(), (1.f/scaleFactor), (1.f/scaleFactor),INTER_LINEAR);
	
	//Rotationswinkel des Gesichtes/der Augen berechnen (Dreieck aufspannen)
		Point2f a = Point2f((leftEyeRect.x+leftEyeRect.size().width/2.f),(leftEyeRect.y+leftEyeRect.size().height/2.f));
		Point2f b = Point2f((rightEyeRect.x+rightEyeRect.size().width/2.f),(rightEyeRect.y+rightEyeRect.size().height/2.f));
		Point2f c = Point2f(b.x,a.y);

		double aside = (b.x-a.x);
		double bside = (a.y-b.y);
		double cside = sqrt(aside*aside+bside*bside);
		double rota = -asin(bside/cside)*180/3.1415f;		

	//Temporäres Material zum kopieren der Brille erstellen
		Mat faceRect_temp(faceRect.size(),glasses.type(),Scalar(0,0,0,0)); 
				
	//Rotationspunkt für Rotation der Brille (respektive des temporären Mats) erstellen
		Point2f rotPt(((a.x+b.x)/2.f)-faceRect.x,((a.y+b.y)/2.f)-faceRect.y);
		
	//Region of Interest zum kopieren der Brille ins temporäre Mat erstellen
		Mat glassesROI_temp = faceRect_temp(Rect(Point2f((((a.x+b.x)/2.f)-faceRect.x)-glasses.size().width/2.f,((a.y+b.y)/2.f)-faceRect.y-glasses.size().height/2.f), glasses.size()));
		
	//Brille per overlayImage mit Alphakanal in diese ROI kopieren
		overlayImage(glassesROI_temp, glasses);

	//Rotationsmatrix für Rotation der Brille (respektive des temporären Mats) erstellen/berechnen
		Mat rotMat = getRotationMatrix2D(rotPt, -rota, 1.0);
	//Der Rotationsmatrix entsprechend rotieren
		warpAffine(faceRect_temp, faceRect_temp, rotMat, faceRect_temp.size());
	//Das temporäre Mat per overlayImage auf das resultFrame kopieren
		overlayImage(resultFrame(faceRect), faceRect_temp);
}

void DrawOnFace::drawHat(cv::Mat& resultFrame, cv::Rect& faceRect, cv::Rect& leftEyeRect, cv::Rect& rightEyeRect){

	//Material für Hut initialisieren
		Mat hat;
		hatImg.copyTo(hat);
		
	//Skalierungsfaktor anhand der Brille berechnen
		scaleFactor = ((float) glassesImg.cols / ((rightEyeRect.x+rightEyeRect.width) - leftEyeRect.x));

	//Hut skalieren
		resize(hat, hat, Size(), 4.f/scaleFactor, 4.f/scaleFactor, INTER_LINEAR);
		
	//Huthöhe verringern sobald man an den Bildrand stößt
		int hatHeight;
		if(faceRect.y-100 <= 0) hatHeight = hat.size().height+faceRect.y-100; else hatHeight=hat.size().height;

	//Region of Interest für Hut festlegen	
		Mat hatROI = resultFrame(Rect(leftEyeRect.x,max((leftEyeRect.y-((rightEyeRect.x+rightEyeRect.width) - leftEyeRect.x))-(hat.size().height/3),0),hat.size().width,hatHeight));

	//Hut per overlayImage in die ROI einfügen	
		overlayImage(hatROI, hat);

}