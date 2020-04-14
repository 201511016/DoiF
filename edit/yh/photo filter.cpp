#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
	String filename = "saram.jpg";
	String filename2 = "vintagefil.jpg";
	String filename3 = "fireworkfil.jpg";
	String filename4 = "concretefil.jpg";

	Mat origin = imread(filename);
	Mat vintagefilter = imread(filename2);
	Mat fireworkfilter = imread(filename3);
	Mat concretefilter = imread(filename4);

	//	imshow("before", src);		//기존 사진
	
	
	Mat Grayimage, Coolimage, Hotimage, Warmimage, Winterimage, Oceanimage, Boneimage, Pinkimage,  Autumnimage;
	cvtColor(origin, Grayimage, COLOR_BGR2GRAY);				//흑백필터
	imshow("Grayimg", Grayimage);

	applyColorMap(origin, Hotimage, COLORMAP_HOT);
	imshow("Hotimg", Hotimage);

	applyColorMap(origin, Winterimage, COLORMAP_WINTER);
	imshow("Winterimg", Winterimage);

	applyColorMap(origin, Oceanimage, COLORMAP_OCEAN);
	imshow("Oceanimg", Oceanimage);

	applyColorMap(origin, Pinkimage, COLORMAP_PINK);
	imshow("Pinkimg", Pinkimage);
	
	applyColorMap(origin, Autumnimage, COLORMAP_AUTUMN);
	imshow("Autumnimg", Autumnimage);
	
	applyColorMap(origin, Boneimage, COLORMAP_BONE);
	imshow("Boneimg", Boneimage);
	
	
	////////////밝기 조정
	Mat Himg, Limg; 
	
	Himg = origin + Scalar(75, 75, 75);

	Limg = origin + Scalar(-75, -75, -75);

	imshow("High Brightness", Himg);

	imshow("Low Brightness", Limg);

	///////////대비 조정
	Scalar avg = mean(origin) / 2.0;
	// 명암대비 감소
	Mat mat = origin * 0.5;
	// 명암대비 증가
	Mat mat2 = origin * 2.0;
	// 평균 화소의 절반 대비 감소
	Mat mat3 = origin * 0.5 + avg[0];
	// 평균 화소의 절반 대비 증가
	Mat mat4 = origin * 2.0 - avg[0];

	// 대비 조정 후 이미지 보기
	imshow("명암대비 감소", mat);
	imshow("명암대비 증가", mat2);
	imshow("평균 화소의 절반 대비 감소", mat3);
	imshow("평균 화소의 절반 대비 증가", mat4);

	
	Mat vintageimg;
	resize(vintagefilter, vintageimg, Size(origin.cols, origin.rows), 0, 0);			//필터를 사진 사이즈에 맞춤.
	Mat fireworkimg;
	resize(fireworkfilter, fireworkimg, Size(origin.cols, origin.rows), 0, 0);
	Mat concreteimg;
	resize(concretefilter, concreteimg, Size(origin.cols, origin.rows), 0, 0);

	Mat vintageresult;
	vintageresult = (0.5)*vintageimg + origin;			//이미지연산
	
	Mat fireworkresult;
	fireworkresult = (0.7)*fireworkimg + origin;
	
	Mat concreteresult;
	concreteresult = (0.5)*concreteimg + (1.2)*origin;

	imshow("Vintage image", vintageresult);					//빈티지 필터 적용
	imshow("Firework image", fireworkresult);				//불꽃놀이 필터 적용
	imshow("Concrete image", concreteresult);				//콘크리트 필터 적용

	imshow("origin", origin);

	waitKey();
	return 0;
}
