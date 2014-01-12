#include "DrawOnFace.h"
#include <math.h>
#include "overlayImage.h"
using namespace cv;

DrawOnFace::DrawOnFace(){

glassesImg = imread("brille0.png", -1);
hatImg = imread("hut0.png", -1);
float scaleFactor;
hatIndex = 0;
glassesIndex = 0;
}
DrawOnFace::~DrawOnFace(){}

const static string hatArray[4] = {"hut0.png","hut1.png","hut2.png","hut3.png"};
const static string glassesArray[4] = {"brille0.png","brille1.png","brille2.png","brille3.png"};

void DrawOnFace::toggleHat(){
	hatIndex = (hatIndex+1)%4;
	std::string temp = hatArray[hatIndex];
	hatImg = imread(temp, -1);
}

void DrawOnFace::toggleGlasses(){
	glassesIndex = (glassesIndex+1)%4;
	std::string temp = glassesArray[glassesIndex];
	glassesImg = imread(temp, -1);
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