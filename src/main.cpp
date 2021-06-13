#include <iostream>
#include <opencv2/opencv.hpp>
#include "functions.h"

using namespace cv;
using namespace std;

int main(){

	Mat src, I1, I2, I3, I4;
	//image input

	string path = samples::findFile("input/1.jpg");
	src = imread( path, IMREAD_GRAYSCALE);
	if(src.empty()){
		return -1;
	}

	//top hat morphological operation

	imtop_hat(src, I1, MORPH_ELLIPSE, 101);

	//image sharpen by unsharp mask (kernel size 5)

	imsharpen(I1, I2);

	//gaussian blur

	GaussianBlur(I2, I3, Size(5,5), 2);

	//histogram stretching

	imadjust(I3, I4);

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


	plotimage(I4, "imagem", 10000);

	return 0;
}
