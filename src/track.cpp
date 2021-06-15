#include "track.h"

void findcircles(Mat& src,vector<Vec3f>& circles, int radio, int ocurenccies, int min_dist, int thresh){
	HoughCircles(src, circles, HOUGH_GRADIENT, 1, min_dist, thresh, ocurenccies, radio, radio);
}
void plotcircles(Mat& src, Mat& dst, vector<Vec3f>& circles){
	int x_center, y_center, radius;
	src.copyTo(dst);
	for(uint i=0; i < circles.size(); i++){
		x_center = circles[i][0];
		y_center = circles[i][1];
		radius   = circles[i][2];
		circle(dst, Point(x_center,y_center), radius, Scalar( 0, 100, 0), 1);
	}
}
void plotcircle(Mat& src, Mat& dst, Vec3f& circle_0, Scalar color){
	int x_center = circle_0[0],
		y_center = circle_0[1],
		radius   = circle_0[2];

	src.copyTo(dst);
	circle( dst, Point(x_center,y_center), radius, color, 1);
}
double euclideandistance(Point a, Point b){
	return sqrt(pow(double(a.x-b.x),0.5) + pow(double(a.y-b.y),0.5));
}

int selectbyproximity(vector<Vec3f>& a77ay,Point p0int, int radius){
	double distance = 0.0,
		   anterior_instance_distance,
		   actual_instance_distance;
	int anterior_instance = 0;
	for(uint i=1;i<a77ay.size();i++){
		distance = euclideandistance(Point(a77ay[i][0],a77ay[i][1]), p0int);
		if(distance < radius){
			actual_instance_distance = distance;
			anterior_instance_distance =
					euclideandistance( Point(a77ay[anterior_instance][0],
											 a77ay[anterior_instance][1]),
											 p0int);
			if(actual_instance_distance < anterior_instance_distance){
				anterior_instance = i;
			}
		}
	}
	return anterior_instance;
}
