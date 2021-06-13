#include <iostream>
#include <opencv2/opencv.hpp>
#include "functions.h"

using namespace cv;
using namespace std;

int main(){

	Mat src;
	src = imread( "input/1.jpg", IMREAD_COLOR);
	if(src.empty()){
		return -1;
	}

	//tophat
	//imagestretching
	//gaussian filter
	//imadjust
	//wiener

	//particle detection

	//find circles
	//select particle
	//save the coordinates of first positions

	//for other images
		//find circles
		//calculate distances
		//get the minimum distace between the selected particle;
		//save new position

	//results


	plotimage(src, "imagem", 30000);

	cout<< "a";
	return 0;
}
