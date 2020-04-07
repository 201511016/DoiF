#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

cv::Mat imgOrg;
cv::Mat img;

//선명한 필터
void sharpFilter(cv::Mat img) {
	//define sharpening kernel
	cv::Mat sharpeningKernel = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

	//result sharp img
	cv::Mat imgSharp;

	filter2D(img, imgSharp, -1, sharpeningKernel);

	cv::namedWindow("sharpe image", cv::WINDOW_AUTOSIZE);
	cv::imshow("sharpe image", imgSharp);
}

//차가운 톤 필터
void coolFilter(cv::Mat img) {
	cv::Mat imgCool;

	//Orignal x-axis values
	float originalValue[] = { 0, 50, 100, 150, 200, 255 };
	//changed points on Y-axis for red and blue channel
	float blueValues[] = { 0, 80, 150, 190, 220, 255 };
	float redValues[] = { 0, 20, 40, 75, 150, 255 };

	//spliting the channels
	std::vector<cv::Mat> channels(3);
	cv::split(img, channels);

	//create lookup table for red channel
	cv::Mat redLookupTable(1, 256, CV_8U);
	uchar* lut = redLookupTable.ptr();
	//apply interpolation and create red channel lookup table
	for (int i = 0; i < 256; i++) {
		int j = 0;
		float a = (float)i;
		while (a > originalValue[j]) {
			j++;
		}
		if (a == originalValue[j]) {
			lut[i] = redValues[j];
			continue;
		}
		float slope = ((float)(redValues[j] - redValues[j - 1])) / ((float)(originalValue[j] - originalValue[j - 1]));
		float constant = redValues[j] - slope * originalValue[j];
		lut[i] = slope * a + constant;
	}

	//create lookup table for blue channel
	cv::Mat blueLookupTable(1, 256, CV_8U);
	lut = blueLookupTable.ptr();
	//apply interpolation and create blue channel lookup table
	for (int i = 0; i < 256; i++) {
		int j = 0;
		float a = (float)i;
		while (a > originalValue[j]) {
			j++;
		}
		if (a == originalValue[j]) {
			lut[i] = blueValues[j];
			continue;
		}
		float slope = ((float)(blueValues[j] - blueValues[j - 1])) / ((float)(originalValue[j] - originalValue[j - 1]));
		float constant = blueValues[j] - slope * originalValue[j];
		lut[i] = slope * a + constant;
	}

	//Apply mapping for red channel
	LUT(channels[2], redLookupTable, channels[2]);

	//Apply mapping for blue channel
	LUT(channels[0], blueLookupTable, channels[0]);

	cv::merge(channels, imgCool);

	//show
	cv::namedWindow("cool result", cv::WINDOW_AUTOSIZE);
	cv::imshow("cool result", imgCool);
}

//따뜻한 톤 필터
void warmFilter(cv::Mat img) {
	cv::Mat imgWarm;

	//Reference points for X-Axis (x축)
	float originalValue[] = { 0,50,100,150,200,255 };
	//Changed points on Y-axis for red and blue channels
	float redValue[] = { 0,80,150,190,220,255 };
	float blueValue[] = { 0,20,40,75,150,255 };

	//split into channels
	//채널 분리
	std::vector<cv::Mat> channels(3);		//channels(3) : 행렬의 채널 개수 반환 (3개)
	cv::split(img, channels);

	cv::Mat lookupTable(1, 256, CV_8U);
	uchar* lut = lookupTable.ptr();

	//Linear Interpolation applied to get values for all the points on X-Axis
	//x축의 모든 점에 대한 값을 얻기 위해 선형 보간 적용
	for (int i = 0; i < 256; i++) {
		int j = 0;
		float a = (float)i;
		while (a > originalValue[j]) {
			j++;
		}
		if (a == originalValue[j]) {
			lut[i] = blueValue[j];
			continue;
		}
		float slope = ((float)(blueValue[j] - blueValue[j - 1])) / ((float)(originalValue[j] - originalValue[j - 1]));
		float constant = blueValue[j] - slope * originalValue[j];
		lut[i] = slope * a + constant;
	}

	cv::Mat lookupTable2(1, 256, CV_8U);
	lut = lookupTable2.ptr();

	//Linear Interpolation applied to get values for all the points on X-Axis
	for (int i = 0; i < 256; i++) {
		int j = 0;
		float a = (float)i;
		while (a > originalValue[j]) {
			j++;
		}
		if (a == originalValue[j]) {
			lut[i] = redValue[j];
			continue;
		}
		float slope = ((float)(redValue[j] - redValue[j - 1])) / ((float)(originalValue[j] - originalValue[j - 1]));
		float constant = redValue[j] - slope * originalValue[j];
		lut[i] = slope * a + constant;
	}
	
	LUT(channels[0], lookupTable, channels[0]);
	LUT(channels[2], lookupTable2, channels[2]);

	//Merge the channels
	merge(channels, imgWarm);

	//show
	cv::namedWindow("warm result", cv::WINDOW_AUTOSIZE);
	cv::imshow("warm result", imgWarm);
}


int main(void) {
	imgOrg = cv::imread("bi.jpg");
	cv::namedWindow("Original image", cv::WINDOW_AUTOSIZE);

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

	cv::waitKey();

	return 0;
}