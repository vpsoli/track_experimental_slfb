#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "functions.h"
#include "track.h"
#include "prepare_file.h"

using namespace cv;
using namespace std;

int main(){

	int particle_id;
	Mat src, gray_scale_src, I1, I2, I3, I4, I5, IC1, IC2;
	vector<Vec3f> beads;
	string file_name;

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

	//select particle

	particle_id = selectbyproximity(beads, Point(src.cols - 200,src.rows/2), 13);
	plotcircle(src, IC2, beads[particle_id]);

	//save the coordinates of first positions

	vector<string> field;
	vector <int> entry;
	file_name = "positions.txt";

	file_name = initializedocument(file_name);

	field.push_back("Frame");
	field.push_back("Eixo x");
	field.push_back("Eixo y");

	entry.push_back(particle_id);
	entry.push_back(beads[particle_id][0]);
	entry.push_back(beads[particle_id][1]);

	createtable(file_name, field);
	inputentry(file_name, entry);

	//for other images
	for(size_t i=2;i < 30; i++){
		//find circles

		string path = samples::findFile("input/1.jpg");
		src = imread( path, IMREAD_COLOR);
		if(src.empty()){
			return -1;
		}

		cvtColor(src, gray_scale_src,COLOR_BGR2GRAY);
		imtop_hat(gray_scale_src, gray_scale_src, MORPH_ELLIPSE, 101);
		imsharpen(gray_scale_src, gray_scale_src);
		GaussianBlur(gray_scale_src, gray_scale_src, Size(5,5), 2);
		imadjust(gray_scale_src, gray_scale_src);
		wienerFilter(gray_scale_src, gray_scale_src);
		findcircles(gray_scale_src, beads, 13, 6, 10,250);

		//calculate distances
		//get the minimum distance between the selected particle;

		particle_id = selectbyproximity(beads, Point(entry[1],entry[2]), beads[0][2]+3);

		if(particle_id < 0){
			cout << "Não há particula próxima.";
			return -1;
		}

		//save new position
		entry.clear();
		entry.push_back(particle_id);
		entry.push_back(beads[particle_id][0]);
		entry.push_back(beads[particle_id][1]);

		inputentry(file_name, entry);

		cout << "Progress: " << i * 100/30 << "%.\n";
	}

	cout << "Progress: 100%. Processamento concluido.";

	//results

	//namedWindow("fig 1.", WINDOW_AUTOSIZE);
	namedWindow("fig 2.", WINDOW_AUTOSIZE);
	//imshow("fig 1.", src);
	imshow("fig 2.", gray_scale_src);

	waitKey(0);

	//plotimage(src, "imagem", 10000);

	return 0;
}
