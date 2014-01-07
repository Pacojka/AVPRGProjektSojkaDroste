#include "Webcamtracking.h"
using namespace cv;
using namespace std;

int main(){
	const string videoPath = "C:\\Users\\paco\\Downloads\\Micro-dance.wmv";
	//const string videoPath = "c:/Entwicklung/micro-dance.mpeg";
	Webcamtracking app;
	if (app.open()){

		app.run();
	}
}