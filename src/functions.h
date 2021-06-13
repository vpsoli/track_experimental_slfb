#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void plotimage(Mat& src, string name, int miliseconds=0);
void imtop_hat(Mat& src,Mat& dst, int structuring_element, int kernel_size);
void imsharpen(Mat& src,Mat& dst, int kernel_size = 5, float std_deviation=1.0, float amount=0.8);
void imadjust(Mat& src,Mat& dst, int tol=1, Vec2i in=Vec2i(0,255), Vec2i out=Vec2i(0,255));
void wienerFilter(Mat& src,Mat& dst, const Size& kernel_size = Size(5,5), double noise_intesity=1.0);
