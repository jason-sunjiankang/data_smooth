/************************
Author£ºsunjiankang
date£º2017/12/11
model1:KalmanFilter
model2:AverageFilter
************************/

//#define model1
#define model2

#include "KalmanFilter.h"
#include "AverageFilter.h"
#include "MouseEvent.h"
#include "ShowData.h"



int main()
{
	
#ifdef model1
	//mouse event && show data
	CMouseEvent ME;
	ShowData SD;
	CAverageFilter AF;
	for (;;)
	{
		//get mouse position
		cv::Point2f mouse_position = ME.getMousePosition();
		cv::Point3f src_data = cv::Point3f(mouse_position.x, mouse_position.y, 0);
	
		//Average filter
		cv::Point3f correct = AF.averageFilter(src_data);
		ME.showMouseImage(src_data, cv::Point3f(0, 0, 0), correct);
		SD.ShowALLData(src_data, correct);
	}
#endif



#ifdef model2
	//mouse event && show data
	CMouseEvent ME;
	ShowData SD;
	//Kalman filter initialization,if q/r=3,then Kalman filter Q/R=100, and so on...
	CKalmanFilter KF;
	int q = 2, r = 1;
	bool need_speed = false;
	KF.intKalmanFilter(q,r, need_speed);

	for (;;)
	{
		//get mouse position
		cv::Point2f mouse_position = ME.getMousePosition();
		cv::Point3f src_data = cv::Point3f(mouse_position.x, mouse_position.y, 0);


		//Kalman filter
		KF.kalmanFilterUpdate(src_data);
		cv::Point3f predict = KF.getKalmanFilterPredict();
		cv::Point3f correct = KF.getKalmanFilterCorrect();
		//show original data(R), predict data(G), correct data(B)
		ME.showMouseImage(cv::Point3f(mouse_position.x, mouse_position.y, 0), predict, correct);
		SD.ShowALLData(src_data, correct);
	}
#endif

	return 0;
}