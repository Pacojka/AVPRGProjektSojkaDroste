#include "DrawEnvironment.h"
#include "overlayImage.h"
using namespace cv;

DrawEnvironment::DrawEnvironment(){

}
DrawEnvironment::~DrawEnvironment(){}

void DrawEnvironment::initialize(int width, int height){
	environment1 = imread("env_TV.png", -1);
	environment2 = imread("env_TV.png", -1);
	environment3 = imread("env_TV.png", -1);
	environment4 = imread("env_TV.png", -1);
	environmentWidth = environment1.size().width;
	environmentHeight = environment1.size().height;
	resize(environment1, environment1, Size(width, height));
	resize(environment2, environment2, Size(width, height));
	resize(environment3, environment3, Size(width, height));
	resize(environment4, environment4, Size(width, height));
	environmentScaleHeight = (float) environment1.size().height/environmentHeight;
	environmentScaleWidth = (float) environment1.size().width/environmentWidth;
	env1_ROI = Rect(Point(70*environmentScaleWidth,130*environmentScaleHeight),Size(913*environmentScaleWidth,669*environmentScaleHeight));
	env2_ROI = Rect(Point(70*environmentScaleWidth,130*environmentScaleHeight),Size(913*environmentScaleWidth,669*environmentScaleHeight));
	env3_ROI = Rect(Point(70*environmentScaleWidth,130*environmentScaleHeight),Size(913*environmentScaleWidth,669*environmentScaleHeight));
	env4_ROI = Rect(Point(70*environmentScaleWidth,130*environmentScaleHeight),Size(913*environmentScaleWidth,669*environmentScaleHeight));
	env1_size = Size(913*environmentScaleWidth,669*environmentScaleHeight);
	env2_size = Size(913*environmentScaleWidth,669*environmentScaleHeight);
	env3_size = Size(913*environmentScaleWidth,669*environmentScaleHeight);
	env4_size = Size(913*environmentScaleWidth,669*environmentScaleHeight);
}


void DrawEnvironment::drawEnvironment(Mat &processedFrame, int number){

	Mat processedFrame_temp;
	processedFrame.copyTo(processedFrame_temp);
	switch(number){
	case 1:
	resize(processedFrame_temp, processedFrame(env1_ROI), env1_size);
	overlayImage(processedFrame, environment1);
	case 2:
	resize(processedFrame_temp, processedFrame(env2_ROI), env2_size);
	overlayImage(processedFrame, environment2);
	case 3:
	resize(processedFrame_temp, processedFrame(env3_ROI), env3_size);
	overlayImage(processedFrame, environment3);
	case 4:
	resize(processedFrame_temp, processedFrame(env4_ROI), env4_size);
	overlayImage(processedFrame, environment4);
	}
	
}