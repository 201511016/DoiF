#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
	String filename = "saram.jpg";
	String filename2 = "vintagefil.jpg";

	Mat origin = imread(filename);
	Mat filter = imread(filename2);
	//	imshow("before", src);		//���� ����
	
	
	Mat Grayimage, Coolimage, Hotimage, Warmimage, Winterimage, Oceanimage, Boneimage, Pinkimage,  Autumnimage;
	cvtColor(origin, Grayimage, COLOR_BGR2GRAY);				//�������
	imshow("Grayimg", Grayimage);

	applyColorMap(origin, Coolimage, COLORMAP_COOL);
	imshow("Coolimg", Coolimage);

	applyColorMap(origin, Hotimage, COLORMAP_HOT);
	imshow("Hotimg", Hotimage);

	applyColorMap(origin, Warmimage, COLORMAP_SPRING);
	imshow("Warmimg", Warmimage);

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
	
	
	////////////��� ����
	Mat Himg, Limg; 
	
	Himg = origin + Scalar(75, 75, 75);

	Limg = origin + Scalar(-75, -75, -75);

	imshow("High Brightness", Himg);

	imshow("Low Brightness", Limg);



	///////////��� ����
	Scalar avg = mean(origin) / 2.0;
	// ��ϴ�� ����
	Mat mat = origin * 0.5;
	// ��ϴ�� ����
	Mat mat2 = origin * 2.0;
	// ��� ȭ���� ���� ��� ����
	Mat mat3 = origin * 0.5 + avg[0];
	// ��� ȭ���� ���� ��� ����
	Mat mat4 = origin * 2.0 - avg[0];

	// ��� ���� �� �̹��� ����
	imshow("��ϴ�� ����", mat);
	imshow("��ϴ�� ����", mat2);
	imshow("��� ȭ���� ���� ��� ����", mat3);
	imshow("��� ȭ���� ���� ��� ����", mat4);

	
	Mat vintageimg;
	resize(filter, vintageimg, Size(origin.cols, origin.rows), 0, 0);			//���͸� ���� ����� ����.

	Mat result;

	result = (0.5)*vintageimg + origin;			//�̹�������
	
	imshow("Vintage image", result);					//��Ƽ�� ����
	imshow("origin", origin);

	waitKey();
	return 0;
}
