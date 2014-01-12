#include "Webcamtracking.h"
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
using namespace cv;
using namespace std;

int main(){
	Webcamtracking app;
	if (app.open()){

	app.run();
	}
}