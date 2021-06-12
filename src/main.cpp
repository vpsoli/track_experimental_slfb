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

	//resultados

	plotimage(src, "imagem", 30000);

	cout<< "a";
	return 0;
}
