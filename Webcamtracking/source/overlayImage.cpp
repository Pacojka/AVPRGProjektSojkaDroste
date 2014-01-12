#include "overlayImage.h"
using namespace cv;
 /*
	Der Quelltext zu dieser Funktion ist eine abgeänderter Version des von Michael Jepson in seinem Blog geposteten Quelltextes zum Überlagern transparenter *.png Dateien.
	Zu finden unter: http://jepsonsblog.blogspot.de/2012/10/overlay-transparent-image-in-opencv.html
 */
void overlayImage(Mat &background, Mat &overlay)
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