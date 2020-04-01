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
//	imshow("before", src);		//���� ����

	Mat dst;
	resize(src, dst, Size(filter.cols, filter.rows), 0, 0);			//������ ���ͻ���� �°� ����

	Mat result;

	result = dst - filter;			//�̹�������
	
	imshow("result", result);
//	imshow("after", dst);		//ũ�� ����� ����
//	imshow("filter", filter);		//���ͻ���
	
	waitKey();
	return 0;
}
