#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void plotimage(Mat& src, string name, int miliseconds=0);
void imtop_hat(Mat& src,Mat& dst, int structuring_element, int kernel_size);
void imadjust(Mat& src,Mat& dst, int tol=1, Vec2i in=Vec2i(0,255), Vec2i out=Vec2i(0,255));
