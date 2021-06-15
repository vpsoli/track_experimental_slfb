#include <iostream>
#include <opencv2/opencv.hpp>
#include "functions.h"
#include "track.h"

using namespace cv;
using namespace std;

int main(){

	Mat src, gray_scale_src, I1, I2, I3, I4, I5, IC1, IC2;
	vector<Vec3f> beads;
	//image input

	string path = samples::findFile("input/1.jpg");
	src = imread( path, IMREAD_COLOR);
	if(src.empty()){
		return -1;
	}

	cvtColor(src, gray_scale_src,COLOR_BGR2GRAY);

	//top hat morphological operation

	imtop_hat(gray_scale_src, I1, MORPH_ELLIPSE, 101);

	//image sharpen by unsharp mask (kernel size 5)

	imsharpen(I1, I2);

	//gaussian blur

	GaussianBlur(I2, I3, Size(5,5), 2);

	//histogram stretching

	imadjust(I3, I4);

	//wiener

	wienerFilter(I4, I5);

	//particle detection

	//find circles

	findcircles(I4, beads, 13, 6, 10,250);
	plotcircles(src, IC1, beads);
	plotcircle(src, IC2, beads[0]);

	//select particle
	//save the coordinates of first positions

	//for other images
		//find circles
		//calculate distances
		//get the minimum distance between the selected particle;
		//save new position

	//results

	//namedWindow("fig 1.", WINDOW_AUTOSIZE);
	namedWindow("fig 2.", WINDOW_AUTOSIZE);
	//imshow("fig 1.", src);
	imshow("fig 2.", IC2);

	waitKey(0);

	//plotimage(src, "imagem", 10000);

	return 0;
}
