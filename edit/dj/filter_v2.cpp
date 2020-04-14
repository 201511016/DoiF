#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

cv::Mat imgOrg;		//원본이미지
cv::Mat img;		//원본의 복사본. 필터 적용을 위함

//이미지가 존재하는지 확인하는 함수
int checkImg(cv::Mat theImg) {
	if (theImg.empty()) {
		std::cout << "Could not open image" << std::endl;
		return -1;
	}
	return 0;
}

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
	cv::Mat blue = cv::imread("F_cool.jpg");
	checkImg(blue);
	cv::Mat imgCool;		//사이즈 조절한 필터 이미지
	cv::Mat res;			//결과 이미지

	//사이즈 조절
	cv::resize(blue, imgCool, cv::Size(img.cols, img.rows), 0, 0);

	//이미지 연산
	res = (0.2)*imgCool + img;

	//show
	cv::namedWindow("cool result", cv::WINDOW_AUTOSIZE);
	cv::imshow("cool result", res);
}

//따뜻한 톤 필터
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

//흑백 필터
void grayFilter(cv::Mat img) {
	cv::Mat res;

	//흑백 전환
	cv::cvtColor(img, res, cv::COLOR_BGR2GRAY);

	cv::namedWindow("gray result", cv::WINDOW_AUTOSIZE);
	cv::imshow("gray result", res);
}

//트랙바를 이용한 밝기 대비 조절 후 이미지 저장
void brightAndContrast(cv::Mat img) {
	cv::namedWindow("trackbar Test", cv::WINDOW_AUTOSIZE);

	cv::Mat imgFrame = img;		//이미지 조절을 위해 새로운 Mat 생성
	
	int contrast = 50;			//대비
	int brightness = 50;		//밝기

	//트랙바 생성. 최대값 100. 실행시 기준점은 50부터
	cv::createTrackbar("Contrast", "trackbar Test", &contrast, 100, NULL, NULL);
	cv::createTrackbar("Brightness", "trackbar Test", &brightness, 100, NULL, NULL);

	while (1)
	{
		//대비 밝기 값 조절
		double iCon = contrast / 50.0;
		int iBright = brightness - 50;
		
		cv::Mat dst;
		// TrackBar에서 설정한 후 dst에 적용
		imgFrame.convertTo(dst, -1, iCon, iBright);

		cv::imshow("trackbar Test", dst);

		//아무키나 누르면 현재 이미지를 저장하고 종료
		if (cv::waitKey(30) >= 0) {
			cv::imwrite("bcimg.jpg", dst);
			break;
		}
	}
	cv::destroyWindow("trackbar Test");
}


int main(void) {
	//원본 이미지 불러오기
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
라운드는 and 연산 생각해보기
bitwiseAnd = cv2.bitwise_and(rectangle, circle)
cv2.imshow("AND", bitwiseAnd)
cv2.waitKey(0)
*/
