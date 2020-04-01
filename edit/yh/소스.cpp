#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
	String filename = "saram.jpg";
	String filename2 = "Rounding.jpg";

	Mat src = imread(filename);
	Mat filter = imread(filename2);
//	imshow("before", src);		//기존 사진

	Mat dst;
	resize(src, dst, Size(filter.cols, filter.rows), 0, 0);			//사진을 필터사이즈에 맞게 변경

	Mat result;

	result = dst - filter;			//이미지연산
	
	imshow("result", result);
//	imshow("after", dst);		//크기 변경된 사진
//	imshow("filter", filter);		//필터사진
	
	waitKey();
	return 0;
}
