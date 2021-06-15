#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void findcircles(Mat& src, vector<Vec3f>& circles, int radio, int ocurenccies, int min_dist, int thresh=100);
void plotcircles(Mat& src, Mat& dst, vector<Vec3f>& circles);
void plotcircle(Mat& src, Mat& dst, Vec3f& circle, Scalar color = Scalar(0,0,186));
