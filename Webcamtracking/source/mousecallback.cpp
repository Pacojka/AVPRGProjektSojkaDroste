#include "mousecallback.h"
#include <opencv2\opencv.hpp>
// Variante 1 für Mouse-Callback: die globalen Variablen werden gesetzt
int mouseClickPositionX = 0;
int mouseClickPositionY = 0;
bool mouseLeftButtonUp = false;

void mouseCallback1(int event, int x, int y, int flags, void*param){
	if(event == cv::EVENT_LBUTTONDOWN){
		mouseLeftButtonUp = true;
	}
	mouseClickPositionX = x;
	mouseClickPositionY = y;
}