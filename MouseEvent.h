#include<opencv2/opencv.hpp>

class CMouseEvent
{
public:
	CMouseEvent();
	~CMouseEvent();

	cv::Point2f  getMousePosition();
	void showMouseImage(cv::Point3f &src_data, cv::Point3f &correct_data, cv::Point3f &predict_data);
	
private:
	int winWidth;
	int winHeight;
	cv::Point2f mouse_position;
};
