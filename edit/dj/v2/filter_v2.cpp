#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

cv::Mat imgOrg;		//�����̹���
cv::Mat img;		//������ ���纻. ���� ������ ����

//�̹����� �����ϴ��� Ȯ���ϴ� �Լ�
int checkImg(cv::Mat theImg) {
	if (theImg.empty()) {
		std::cout << "Could not open image" << std::endl;
		return -1;
	}
	return 0;
}

//������ ����
void sharpFilter(cv::Mat img) {
	//define sharpening kernel
	cv::Mat sharpeningKernel = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

	//result sharp img
	cv::Mat imgSharp;

	filter2D(img, imgSharp, -1, sharpeningKernel);

	cv::namedWindow("sharpe image", cv::WINDOW_AUTOSIZE);
	cv::imshow("sharpe image", imgSharp);
}

//������ �� ����
void coolFilter(cv::Mat img) {
	cv::Mat blue = cv::imread("F_cool.jpg");
	checkImg(blue);
	cv::Mat imgCool;		//������ ������ ���� �̹���
	cv::Mat res;			//��� �̹���

	//������ ����
	cv::resize(blue, imgCool, cv::Size(img.cols, img.rows), 0, 0);

	//�̹��� ����
	res = (0.2)*imgCool + img;

	//show
	cv::namedWindow("cool result", cv::WINDOW_AUTOSIZE);
	cv::imshow("cool result", res);
}

//������ �� ����
void warmFilter(cv::Mat img) {
	cv::Mat warm = cv::imread("F_warm.jpg");
	checkImg(warm);
	cv::Mat imgWarm;
	cv::Mat res;

	cv::resize(warm, imgWarm, cv::Size(img.cols, img.rows), 0, 0);

	res = (0.1)*imgWarm + img;

	//show
	cv::namedWindow("warm result", cv::WINDOW_AUTOSIZE);
	cv::imshow("warm result", res);
}

//��� ����
void grayFilter(cv::Mat img) {
	cv::Mat res;

	//��� ��ȯ
	cv::cvtColor(img, res, cv::COLOR_BGR2GRAY);

	cv::namedWindow("gray result", cv::WINDOW_AUTOSIZE);
	cv::imshow("gray result", res);
}

//Ʈ���ٸ� �̿��� ��� ��� ���� �� �̹��� ����
void brightAndContrast(cv::Mat img) {
	cv::namedWindow("trackbar Test", cv::WINDOW_AUTOSIZE);

	cv::Mat imgFrame = img;		//�̹��� ������ ���� ���ο� Mat ����
	
	int contrast = 50;			//���
	int brightness = 50;		//���

	//Ʈ���� ����. �ִ밪 100. ����� �������� 50����
	cv::createTrackbar("Contrast", "trackbar Test", &contrast, 100, NULL, NULL);
	cv::createTrackbar("Brightness", "trackbar Test", &brightness, 100, NULL, NULL);

	while (1)
	{
		//��� ��� �� ����
		double iCon = contrast / 50.0;
		int iBright = brightness - 50;
		
		cv::Mat dst;
		// TrackBar���� ������ �� dst�� ����
		imgFrame.convertTo(dst, -1, iCon, iBright);

		cv::imshow("trackbar Test", dst);

		//�ƹ�Ű�� ������ ���� �̹����� �����ϰ� ����
		if (cv::waitKey(30) >= 0) {
			cv::imwrite("bcimg.jpg", dst);
			break;
		}
	}
	cv::destroyWindow("trackbar Test");
}


int main(void) {
	//���� �̹��� �ҷ�����
	imgOrg = cv::imread("yeri.jpg");
	cv::namedWindow("Original image", cv::WINDOW_AUTOSIZE);

	//checkImg(imgOrg);
	if (imgOrg.empty()) {
		std::cout << "Could not open image" << std::endl;
		return -1;
	}

	//show origonal image
	cv::imshow("Original image", imgOrg);

	//copy original image
	img = imgOrg.clone();

	//adjust filter
	sharpFilter(img);
	coolFilter(img);
	warmFilter(img);
	grayFilter(img);
	brightAndContrast(img);

	cv::waitKey();

	return 0;
}
/*
����� and ���� �����غ���
bitwiseAnd = cv2.bitwise_and(rectangle, circle)
cv2.imshow("AND", bitwiseAnd)
cv2.waitKey(0)
*/
