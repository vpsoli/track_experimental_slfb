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
void imsharpen(Mat& src,Mat& dst, int kernel_size, float std_deviation,float amount){
	GaussianBlur(src, dst, Size(kernel_size,kernel_size), std_deviation, std_deviation);
	addWeighted(src, 1.0 + amount, dst, -amount, 0, dst);
}
//
void imadjust(Mat& src,Mat& dst, int tol, Vec2i in, Vec2i out){

	// src : input CV_8UC1 image

	// dst : output CV_8UC1 image

	// tol : tolerance, from 0 to 100.

	// in  : src image bounds

	// out : dst image buonds

	dst = src.clone();

	tol = max(0, min(100, tol));

	if (tol > 0){

		// Compute in and out limits

		// Histogram
		vector<int> hist(256, 0);
		for (int r = 0; r < src.rows; ++r) {
			for (int c = 0; c < src.cols; ++c) {
				hist[src.at<uchar>(r,c)]++;
			}
		}

		// Cumulative histogram
		vector<int> cumulative = hist;
		for (uint i = 1; i < hist.size(); ++i) {
			cumulative[i] = cumulative[i - 1] + hist[i];
		}

		// Compute bounds
		int total = src.rows * src.cols;
		int low_bound = total * tol / 100;
		int upp_bound = total * (100-tol)/100;
		in[0] = distance(cumulative.begin(), lower_bound(cumulative.begin(), cumulative.end(), low_bound));
		in[1] = distance(cumulative.begin(), lower_bound(cumulative.begin(), cumulative.end(), upp_bound));
	}

	// Stretching
	float scale = float(out[1] - out[0]) / float(in[1] - in[0]);

	for (int r = 0; r < dst.rows; ++r){
		for (int c = 0; c < dst.cols; ++c){
			int vs = max(src.at<uchar>(r, c) - in[0], 0);
			int vd = min(int(vs * scale + 0.5f) + out[0], out[1]);
			dst.at<uchar>(r, c) = saturate_cast<uchar>(vd);
		}
	}
}
void wienerFilter(Mat& src,Mat& dst, const Size& kernel_size, double noise_intesity){

	//int width = src.cols, height = src.rows;
	Mat1d filtered_src = src,
		  mean = src,
		  sq_box_filtered_src = src,
		  variance, average_variance;

	src.copyTo(dst);

	//src.copyTo(filtered_src);
	//src.copyTo(sq_box_filtered_src);

	boxFilter(src, filtered_src, CV_64F, kernel_size, Point(-1,-1),true,BORDER_REPLICATE);
	sqrBoxFilter(src, sq_box_filtered_src, CV_64F, kernel_size, Point(-1,-1),true,BORDER_REPLICATE);

	filtered_src.copyTo(mean);

	variance = sq_box_filtered_src - filtered_src.mul(filtered_src);

	if(noise_intesity < 0){
		reduce(variance, average_variance, 1, REDUCE_SUM, -1);
		reduce(average_variance, average_variance, 0, REDUCE_SUM, -1);
		noise_intesity = variance.at<float>(0,0)/(float)(src.rows*src.cols);
	}

	imshow("imagem", variance);
	waitKey(0);

	cout << noise_intesity;

	for (int r = 0; r < src.rows; ++r){
		// get row pointers
		for (int c = 0; c < src.cols; ++c) {
			dst.at<uchar>(r,c) =
			saturate_cast<uchar>(mean.at<double>(r,c) + max( 0.0, variance.at<double>(r,c) - noise_intesity)*
			max(variance.at<double>(r,c),noise_intesity)*(src.at<uchar>(r,c) - mean.at<double>(r,c)));
		}
	}

}
/*void imwiener(){

}*/
