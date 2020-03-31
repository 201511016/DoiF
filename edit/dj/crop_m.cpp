/*
���� ���� ��� : ���콺�� �巡���ؼ� ���� ���� �� Ű���忡�� ���ϴ� Ű�� ����
�� â�� �Բ� ũ�ӵ� �̹����� ��
Ű���带 ������ ũ�ӵ� �̹����� ���� ����Ǹ鼭 �����

�������� : ���� ������ �巡�װ� �ƴ� �� �𼭸��� ���������� ������ �� �ִ� ��� �ʿ�
*/

#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat imgOrg;						//Original image
cv::Mat img;						//copy original image

cv::Rect rect(0, 0, 0, 0);			//selection Rect
cv::Point p1(0, 0);					//start point
cv::Point p2(0, 0);					//end point

static bool clicked = false;		//mouse activation

//�ʱ� ������ �̹��� ������ ����
void fix_area() {
	if (rect.width > img.cols - rect.x)		//set width
		rect.width = img.cols - rect.x;
	if (rect.height > img.rows - rect.y)	//set height
		rect.height > img.rows - rect.y;
	if (rect.x < 0)
		rect.x = 0;
	if (rect.y < 0)
		rect.y = 0;
}

void draw() {
	img = imgOrg.clone();										//copy original image
	fix_area();
	cv::rectangle(img, rect, cv::Scalar(0, 0, 255), 2, 8, 0);	//draw rectangle
	cv::imshow("Original image", img);
}

void onMouse(int event, int x, int y, int flag, void* user_data) {
	switch (event) {
	case cv::EVENT_LBUTTONDOWN:		//���콺 ���� ��ư�� ������ ��
		clicked = true;
		p1.x = x;					//Ŭ���� ������ ������
		p1.y = y;
		p2.x = x;
		p2.y = y;
		break;
	case cv::EVENT_LBUTTONUP:		//���콺 ���� ��ư�� �� ��
		clicked = false;
		p2.x = x;
		p2.y = y;
		break;
	case cv::EVENT_MOUSEMOVE:		//���콺�� ������ ��
		if (clicked) {				//true�� �� Ȱ��ȭ
			p2.x = x;
			p2.y = y;
		}
		break;

	default:
		break;
	}
	//�簢�� ���� ����
	if (p1.x > p2.x) {
		rect.x = p2.x;
		rect.width = p1.x - p2.x;
	}
	else {
		rect.x = p1.x;
		rect.width = p2.x - p1.x;
	}
	if (p1.y > p2.y) {
		rect.y = p2.y;
		rect.height = p1.y - p2.y;
	}
	else {
		rect.y = p1.y;
		rect.height = p2.y - p1.y;
	}
	draw();
}

int main(void) {
	imgOrg = cv::imread("326.jpg");	//load original image
	cv::namedWindow("Original image", cv::WINDOW_AUTOSIZE);
	cv::setMouseCallback("Original image", onMouse, NULL);
	

	//error
	if (imgOrg.empty()) {
		std::cout << "Could not open image" << std::endl;
		return -1;
	}

	//show original image
	cv::imshow("Original image", imgOrg);

	if (cv::waitKey()) {
		//croped image
		cv::Mat imgCrop = imgOrg(rect);	
		cv::namedWindow("Croped image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Croped image", imgCrop);
		cv::waitKey();
		//save croped image
		cv::imwrite("cropImg.jpg", imgCrop);					
	}

	return 0;
}
