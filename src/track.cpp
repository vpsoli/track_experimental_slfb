#include "track.h"

void findcircles(Mat& src,vector<Vec3i>& circles, int radio, int ocurenccies, int min_dist, int thresh){
	HoughCircles(src, circles, HOUGH_GRADIENT, 1, min_dist, thresh, ocurenccies, radio, radio + 1);
}
void plotcircles(Mat& src, vector<Vec3i>& circles){
	for(uint i=0; i < circles.size(); i++){

	}
}
