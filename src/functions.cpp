#include "functions.h"

void plotimage(Mat& src,string name, int miliseconds){
	namedWindow("window",WINDOW_AUTOSIZE);
	imshow("window", src);
	waitKey();
}

void imtop_hat(Mat& src,Mat& dst, int structuring_element, int kernel_size){
	Mat element = getStructuringElement(structuring_element,
										Size(kernel_size,kernel_size),
										Point(kernel_size/2,kernel_size/2));
	morphologyEx(src, dst, MORPH_TOPHAT, element);
}
void imsharpen(Mat& src,Mat& dst, int kernel_size, float std_deviation){
	GaussianBlur(src, dst, Size(kernel_size,kernel_size), std_deviation, std_deviation);
	addWeighted(src, 1.0, dst, 0.5, 0, dst);
}
//
void imadjust(Mat& src,Mat& dst, int tol, Vec2i in, Vec2i out){
	// src : input CV_8UC1 image
	    // dst : output CV_8UC1 imge
	    // tol : tolerance, from 0 to 100.
	    // in  : src image bounds
	    // out : dst image buonds

	    dst = src.clone();

	    tol = max(0, min(100, tol));

	    if (tol > 0)
	    {
	        // Compute in and out limits

	        // Histogram
	        vector<int> hist(256, 0);
	        for (int r = 0; r < src.rows; ++r) {
	            for (int c = 0; c < src.cols; ++c) {
	                hist[src.at<int>(r,c)]++;
	            }
	        }

	        // Cumulative histogram
	        vector<int> cum = hist;
	        for (uint i = 1; i < hist.size(); ++i) {
	            cum[i] = cum[i - 1] + hist[i];
	        }

	        // Compute bounds
	        int total = src.rows * src.cols;
	        int low_bound = total * tol / 100;
	        int upp_bound = total * (100-tol) / 100;
	        in[0] = distance(cum.begin(), lower_bound(cum.begin(), cum.end(), low_bound));
	        in[1] = distance(cum.begin(), lower_bound(cum.begin(), cum.end(), upp_bound));

	    }

	    // Stretching
	    float scale = float(out[1] - out[0]) / float(in[1] - in[0]);
	    for (int r = 0; r < dst.rows; ++r)
	    {
	        for (int c = 0; c < dst.cols; ++c)
	        {
	            int vs = max(src.at<int>(r, c) - in[0], 0);
	            int vd = min(int(vs * scale + 0.5f) + out[0], out[1]);
	            dst.at<int>(r, c) = saturate_cast<uchar>(vd);
	        }
	    }
}
void imwiener(){

}
