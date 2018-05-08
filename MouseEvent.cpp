#include "MouseEvent.h"

cv::Point  mouse_position_get;
//鼠标回调函数写在类里失效了，暂时把它拿出来
void mouseEvent(int event, int x, int y, int flags, void *param)
{
	if (event == CV_EVENT_MOUSEMOVE)
	{
		mouse_position_get = cv::Point(x, y);
	}
}


CMouseEvent::CMouseEvent()
{
	winWidth = 800;
	winHeight = 600;
}
CMouseEvent::~CMouseEvent()
{

}

cv::Point2f CMouseEvent::getMousePosition()
{
	cv::setMouseCallback("Kalman", mouseEvent);
	mouse_position = mouse_position_get;
	return mouse_position;
}


void  CMouseEvent::showMouseImage(cv::Point3f &src_data, cv::Point3f &correct_data, cv::Point3f &predict_data)
{
	cv::Mat img = cv::Mat(winWidth, winHeight, CV_8UC3);
	img.setTo(166);

	cv::circle(img, cv::Point2f(src_data.x, src_data.y), 5, CV_RGB(255, 0, 0), 2);
	cv::circle(img, cv::Point2f(correct_data.x, correct_data.y), 5, CV_RGB(0, 255, 0), 2);
	cv::circle(img, cv::Point2f(predict_data.x, predict_data.y), 5, CV_RGB(0, 0, 255), 2);
	cv::imshow("Kalman", img);
	cv::waitKey(1);
}


