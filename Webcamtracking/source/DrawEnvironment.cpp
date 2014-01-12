#include "DrawEnvironment.h"
using namespace cv;

DrawEnvironment::DrawEnvironment(){
}
DrawEnvironment::~DrawEnvironment(){}


void DrawEnvironment::overlayImage(Mat &background, Mat &overlay)
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



void DrawEnvironment::drawEnvironment(Mat &processedFrame){

	Mat environment = imread("env_TV.png", -1);
	double environmentScaleWidth = 0.f;
	double environmentScaleHeight = 0.f;
	int environmentWidth = environment.size().width;
	int environmentHeight = environment.size().height;

	std::cout << "enviromentWidth: " << environmentWidth << std::endl;
	std::cout << "enviromentHeight: " << environmentHeight << std::endl;
	std::cout << "processedFrame.size(): " << processedFrame.size() << std::endl;

	resize(environment, environment, processedFrame.size());

	std::cout << "environment.size(): " << environment.size() << std::endl;

	environmentScaleHeight = (float) environment.size().height/environmentHeight;
	environmentScaleWidth = (float) environment.size().width/environmentWidth;

	std::cout << "enviromentScaleWidth: " << environmentScaleWidth << std::endl;
	std::cout << "enviromentScaleHeight: " << environmentScaleHeight << std::endl;

	Mat processedFrame_temp;
	resize(processedFrame, processedFrame_temp, Size(913*environmentScaleWidth,669*environmentScaleHeight));

	Mat environment_BG(processedFrame.size(), processedFrame.type());
	Mat frameROI = environment_BG(Rect(Point(70*environmentScaleWidth,130*environmentScaleHeight),Size(913*environmentScaleWidth,669*environmentScaleHeight)));

	processedFrame_temp.copyTo(frameROI);
	overlayImage(environment_BG, environment);
	environment_BG.copyTo(processedFrame);
	
}