#include "BackgroundSubstraction.h"
using namespace cv;
using namespace std;

int main(){
	const string videoPath = "C:\\Users\\paco\\Downloads\\Micro-dance.wmv";
	//const string videoPath = "c:/Entwicklung/micro-dance.mpeg";
	Backgroundsubstraction app;
	if (app.open()){
		app.run();
	}
}