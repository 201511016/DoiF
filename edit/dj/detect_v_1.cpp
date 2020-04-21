#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	//load original image
	String filename = "suzy.png";
	Mat src = imread(filename);

	//check if file exists
	if (src.empty()) {
		cout << "Could not open file\n";
		return -1;
	}

	//연산에 활용할 이미지를 원본 이미지에서 복사
	Mat img = src.clone();

	//흰 배경을 검은색으로 전환 --> 응 안돼
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (img.at<Vec3b>(i, j) == Vec3b(255, 255, 255)) {
				img.at<Vec3b>(i, j)[0] = 0;
				img.at<Vec3b>(i, j)[1] = 0;
				img.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}
	imshow("black and white", img);
	
	//선명하게 만들 커널
	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);

	//라플라스
	Mat imgLa;
	filter2D(img, imgLa, CV_32F, kernel);
	Mat sharp;
	img.convertTo(sharp, CV_32F);
	Mat dst = sharp - imgLa;

	//8비트 그레이스케일
	dst.convertTo(dst, CV_8UC3);
	imgLa.convertTo(imgLa, CV_8UC3);

	//미리보기
	imshow("sharped img", dst);

	//threshold(두채널로 만들어주는) 어쩌구
	Mat gray;
	cvtColor(dst, gray, COLOR_RGB2GRAY);
	threshold(gray, gray, 40, 255, THRESH_BINARY | THRESH_OTSU);

	//mi ri bo gi
	imshow("binary img", gray);


	//백그라운드 얻기
	/*
	Mat m;
	m.ones(3, 3, CV_8U);
	erode(gray, gray, m);
	dilate(gray, opening, m);
	dilate(opening, Bg, m, Point(-1, -1), 3);
	*/

	//디스턴스 어쩌구
	Mat dist;
	distanceTransform(gray, dist, DIST_L2, 3);
	normalize(dist, dist, 0, 1.0, NORM_MINMAX);

	//preshow
	imshow("distance", dist);


	//foreground
	threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);
	/*
	Fg.convertTo(Fg, CV_8U, 1, 0);
	subtract(Bg, Fg, unknown);
	*/

	//디스턴스 이미지 팽창
	Mat kernel2 = Mat::ones(3, 3, CV_8U);
	dilate(dist, dist, kernel2);

	//preview
	imshow("peaks", dist);
	

	//여기서부터 오류나는 것 같음


	Mat dist_8u;
	dist.convertTo(dist_8u, CV_8U);

	//find total markers
	vector<vector<Point> > contours;
	findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);



	//connect component
	/*
	connectedComponents(Fg, markers);
	for (int i = 0; i < markers.rows; i++) {
		for (int j = 0; j < markers.cols; j++) {
			markers.ptr<int>(i, j)[0] = markers.ptr<uchar>(i, j)[0] + 1;
			if (unknown.ptr<uchar>(i, j)[0] == 255) {
				markers.ptr<int>(i, j)[0] = 0;
			}
		}
	}
	cvtColor(img, img, COLOR_RGBA2RGB, 0);
	watershed(img, markers);
	*/
	//waterched알고리즘에서 마커이미지 생성
	Mat markers = Mat::zeros(dist.size(), CV_32S);

	//draw fg markers
	for (size_t i = 0; i < contours.size(); i++) {
		drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
	}
	//draw bg markers
	circle(markers, Point(5, 5), 3, Scalar(255), -1);
	imshow("markers", markers*10000);

	//watershed
	watershed(dst, markers);

	Mat mark;
	markers.convertTo(mark, CV_8U);
	bitwise_not(mark, mark);

	// Generate random colors
	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++)
	{
		int b = theRNG().uniform(0, 256);
		int g = theRNG().uniform(0, 256);
		int r = theRNG().uniform(0, 256);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	Mat finImg = Mat::zeros(markers.size(), CV_8UC3);
	//fill
	for (int i = 0; i < markers.rows; i++) {
		for (int j = 0; i < markers.cols; j++) {
			int index = markers.at<int>(i, j);
			if (index > 0 && index <= static_cast<int>(contours.size())) {
				finImg.at<Vec3b>(i, j) = colors[index - 1];
			}
		}
	}

	imshow("Final Image", finImg);

	//draw barriers
	/*
	for (int i = 0; i < markers.rows; i++) {
		for (int j = 0; j < markers.cols; j++) {
			if(markers.ptr<int>(i, j)[0] == -1){
				img.ptr<uchar>(i, j)[0] == 255;
				img.ptr<uchar>(i, j)[1] == 0;
				img.ptr<uchar>(i, j)[2] == 0;
			}
		}
	}
	*/

	waitKey();


	return 0;
}

