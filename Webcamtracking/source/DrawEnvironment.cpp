#include "DrawEnvironment.h"
#include "overlayImage.h"
using namespace cv;

DrawEnvironment::DrawEnvironment(){

}
DrawEnvironment::~DrawEnvironment(){}

void DrawEnvironment::initialize(int width, int height){
	environment1 = imread("env_TV.png", -1);
	environment2 = imread("env_News.png", -1);
	environment3 = imread("env_Cinema.png", -1);
	environment4 = imread("env_Frame.png", -1);
	environmentWidth = environment1.size().width;
	environmentHeight = environment1.size().height;
	resize(environment1, environment1, Size(width, height));
	resize(environment2, environment2, Size(width, height));
	resize(environment3, environment3, Size(width, height));
	resize(environment4, environment4, Size(width, height));
	environmentScaleHeight = (float) environment1.size().height/environmentHeight;
	environmentScaleWidth = (float) environment1.size().width/environmentWidth;
	env1_size = Size(800*environmentScaleWidth,600*environmentScaleHeight);
	env2_size = Size(641*environmentScaleWidth,481*environmentScaleHeight);
	env3_size = Size(800*environmentScaleWidth,600*environmentScaleHeight);
	env4_size = Size(958*environmentScaleWidth,668*environmentScaleHeight);
	env1_ROI = Rect(Point(80*environmentScaleWidth,130*environmentScaleHeight),env1_size);
	env2_ROI = Rect(Point(47*environmentScaleWidth,150*environmentScaleHeight),env2_size);
	env3_ROI = Rect(Point(200*environmentScaleWidth,113*environmentScaleHeight),env3_size);
	env4_ROI = Rect(Point(122*environmentScaleWidth,114*environmentScaleHeight),env4_size);
}


void DrawEnvironment::drawEnvironment(Mat &processedFrame, int number){

	Mat processedFrame_temp;
	processedFrame.copyTo(processedFrame_temp);
	switch(number){
	case 1:
	resize(processedFrame_temp, processedFrame(env1_ROI), env1_size);
	overlayImage(processedFrame, environment1);
	break;
	case 2:
	resize(processedFrame_temp, processedFrame(env2_ROI), env2_size);
	overlayImage(processedFrame, environment2);
	break;
	case 3:
	resize(processedFrame_temp, processedFrame(env3_ROI), env3_size);
	overlayImage(processedFrame, environment3);
	break;
	case 4:
	resize(processedFrame_temp, processedFrame(env4_ROI), env4_size);
	overlayImage(processedFrame, environment4);
	break;
	}
	
}