#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void findcircles(Mat& src, vector<Vec3i>& circles, int radio, int ocurenccies, int min_dist, int thresh=100);
