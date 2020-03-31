#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void ft_Geom_Shift(Mat &image1, Mat &image2, int dx, int dy);

int main(int argc, char** argv)
{
	// Load the image
	Mat imgOriginal = imread("hwasa.jpg", 1);
	Mat imgReduction1;
	Mat imgReduction2;

	cv::resize(imgOriginal, imgReduction1, Size(imgOriginal.cols * 1 / 4, imgOriginal.rows * 1 / 4), 0, 0, 1);
	// 원본을 행과 열 4분의 1 크기로 조정하여 ImgReduction에 저장

	cv::resize(imgReduction1, imgReduction2, Size(imgReduction1.rows, imgReduction1.cols), 0, 0, 1);
	// 90도, 270도 회전을 위해 rows, cols 크기 변환한 이미지 ImgReduction1에 저장

	imshow("Reduction image1", imgReduction1); 
	imshow("Reduction image2", imgReduction2);

	//show the original image
	const char* pzOriginalImage = "Original Image";
	namedWindow(pzOriginalImage, 1);
	imshow(pzOriginalImage, imgOriginal);

	//rotated image
	const char* pzRotatedImage1 = "Rotated Image1";
	namedWindow(pzRotatedImage1, 1);

	const char* pzRotatedImage2 = "Rotated Image2";
	namedWindow(pzRotatedImage2, 1);

	const char* pzRotatedImage3 = "Rotated Image3";
	namedWindow(pzRotatedImage3, 1);

	const char* pzRotatedImage4 = "Rotated Image4";
	namedWindow(pzRotatedImage4, 1);

	// 회전을 위한 중심 포인트 지정
	int iImageHeight1 = imgReduction1.rows / 2;
	int iImageWidth1 = imgReduction1.cols / 2;

	int iImageHeight2 = imgReduction2.rows / 2;
	int iImageWidth2 = imgReduction2.cols / 2;

	int iImageHeight3 = imgOriginal.rows / 2;
	int iImageWidth3 = imgOriginal.cols / 2;

	// 이동한 이미지 출력을 위한 imgTemp 생성 >> 예외 발생 수정 필요
	// int imgCstate = (imgOriginal.channels() == 1) ? CV_8UC1 : CV_8UC3;
	Mat imgTemp(imgReduction2.rows, imgReduction2.cols, imgOriginal.type(), Scalar(255));

	imshow("Temp1", imgTemp);

	//이미지를 imgReducton2 중심으로 이동
	ft_Geom_Shift(imgReduction1, imgTemp, iImageWidth2 - iImageWidth1, iImageHeight1 - iImageHeight2);

	// float data[2][3] = {{1, 0, iImageWidth2 - iImageWidth1}, {0, 1, iImageHeight1 - iImageHeight2}};
	// Mat trans(Size(1, 2), CV_32FC3, data);
	// cout << trans << endl;
	// namedWindow("img", WINDOW_FREERATIO);
	// imshow("img", trans);

	//warpAffine(imgReduction1, imgTemp, trans, imgReduction2.size());

	imshow("Temp2", imgTemp);


	//90도 회전
	Mat matRotation1 = getRotationMatrix2D(Point(iImageWidth1, iImageHeight1), 90, 1);

	Mat imgRotated1;
	warpAffine(imgTemp, imgRotated1, matRotation1, imgReduction1.size());

	imshow(pzRotatedImage1, imgRotated1);


	//180도 회전
	Mat matRotation2 = getRotationMatrix2D(Point(iImageWidth1, iImageHeight1), 180, 1);

	Mat imgRotated2;
	warpAffine(imgReduction1, imgRotated2, matRotation2, imgReduction1.size());

	imshow(pzRotatedImage2, imgRotated2);


	//270도 회전
	Mat matRotation3 = getRotationMatrix2D(Point(iImageWidth1, iImageHeight1), 270, 1);

	Mat imgRotated3;
	warpAffine(imgTemp, imgRotated3, matRotation3, imgReduction1.size());

	imshow(pzRotatedImage3, imgRotated3);


	//360도 회전
	Mat matRotation4 = getRotationMatrix2D(Point(iImageWidth1, iImageHeight1), 360, 1);

	Mat imgRotated4;
	warpAffine(imgReduction1, imgRotated4, matRotation4, imgReduction1.size());

	imshow(pzRotatedImage4, imgRotated4);

	waitKey(0);

	return 0;
}

void ft_Geom_Shift(Mat &image1, Mat &image2, int dx, int dy) {
	for (int y = dy; y < image2.rows; y++) {
		for (int x = dx; x < image2.cols; x++) {

			// 0~255 level (흑백영상)
			if (image1.channels() == 1) {
				uchar data = image1.at<uchar>(y - dy, x - dx);
				image2.at<uchar>(y, x) = data;
			}

			// RGB label (컬러영상)
			else if (image1.channels() == 3) {
				Vec3b colVal = image1.at<Vec3b>(y - dy, x - dx);
				image2.at<Vec3b>(y, x) = colVal;
			}
		}
	}
}