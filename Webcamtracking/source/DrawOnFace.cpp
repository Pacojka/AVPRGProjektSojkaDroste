#include "DrawOnFace.h"
using namespace cv;

DrawOnFace::DrawOnFace(){}
DrawOnFace::~DrawOnFace(){}

void overlayImage(Mat &background, Mat &overlay)
{
	for(int y = 0; y < background.rows; y++){
		for(int x = 0; x < background.cols; x++){
			//Opacity ("Durchsichtigkeit") des aktuelles Pixels berechnen -> (Alphakanal / 255) = [0-1]
				double opacity = ((double)overlay.data[y * overlay.step + x * overlay.channels() + 3]) / 255.f;
					//Fuer jeden Channel einzeln die Opacity setzen
						for(int c = 0; opacity > 0 && c < background.channels(); c++)
						{
						//ovPx = aktueller (Uchar-)Wert des Overlaybildes
							uchar ovPx = overlay.data[y * overlay.step + x * overlay.channels() + c];
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
		Mat glasses = imread("C:\\Users\\User\\Pictures\\brille.png", -1);

	//Brillengröße=(Brillenabstand/Augenabstand)
		float scaleFactor = ((float) glasses.cols /((rightEyeRect.x+rightEyeRect.width) - leftEyeRect.x));
		//cout << "Skalierungsfaktor: 1 durch " << scaleFactor << endl;

	//Brillengröße dem Skalierungsfaktor entsprechend verändern
		resize(glasses, glasses, Size(), (1.f/scaleFactor), (1.f/scaleFactor),INTER_LINEAR);
	//Region of Interest (also Bildbereich in den die Brille kopiert werden soll) festlegen
		Mat glassesROI = resultFrame(Rect(leftEyeRect.x,leftEyeRect.y,glasses.size().width,glasses.size().height));
	
	//Brille (mit Alphakanal) ins Bild kopieren
		overlayImage(glassesROI, glasses);

	//HUT
	//Mat für Hut initialisieren (inkl. Alphakanal)
		Mat hat = imread("C:\\Users\\User\\Pictures\\hut.png", -1);


		float scaleFactor2 = ((float) hat.cols / faceRect.width);
		resize(hat, hat, Size(), scaleFactor2, scaleFactor2, INTER_LINEAR);
		Mat hatROI = resultFrame(Rect(faceRect.x+30,max(faceRect.y-100,0),hat.size().width,hat.size().height));

		overlayImage(hatROI, hat);

}
