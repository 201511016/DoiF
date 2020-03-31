/*
범위 설정 방법 : 마우스로 드래그해서 영역 설정 후 키보드에서 원하는 키를 누름
새 창과 함께 크롭된 이미지가 뜸
키보드를 누르면 크롭된 이미지가 새로 저장되면서 종료됨

수정사항 : 선택 영역을 드래그가 아닌 각 모서리를 자율적으로 조절할 수 있는 방법 필요
*/

#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat imgOrg;						//Original image
cv::Mat img;						//copy original image

cv::Rect rect(0, 0, 0, 0);			//selection Rect
cv::Point p1(0, 0);					//start point
cv::Point p2(0, 0);					//end point

static bool clicked = false;		//mouse activation

//초기 영역을 이미지 안으로 설정
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
	img = imgOrg.clone();						//copy original image
	fix_area();
	cv::rectangle(img, rect, cv::Scalar(0, 0, 255), 2, 8, 0);	//draw rectangle
	cv::imshow("Original image", img);
}

void onMouse(int event, int x, int y, int flag, void* user_data) {
	switch (event) {
	case cv::EVENT_LBUTTONDOWN:		//마우스 왼쪽 버튼이 눌렸을 때
		clicked = true;
		p1.x = x;			//클릭한 지점이 시작점
		p1.y = y;
		p2.x = x;
		p2.y = y;
		break;
	case cv::EVENT_LBUTTONUP:		//마우스 왼쪽 버튼을 뗄 때
		clicked = false;
		p2.x = x;
		p2.y = y;
		break;
	case cv::EVENT_MOUSEMOVE:		//마우스를 움직일 때
		if (clicked) {			//true일 때 활성화
			p2.x = x;
			p2.y = y;
		}
		break;

	default:
		break;
	}
	//사각형 영역 설정
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
	imgOrg = cv::imread("bi.jpg");	//load original image
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
