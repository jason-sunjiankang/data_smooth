#include<opencv2/opencv.hpp>


class CKalmanFilter
{
public:
	CKalmanFilter();
	~CKalmanFilter();
	
	void intKalmanFilter(int &m_Q, int &m_R, bool &need_speed);
	void kalmanFilterUpdate(cv::Point3f &src_data);

	cv::Point3f getKalmanFilterPredict();
	cv::Point3f getKalmanFilterCorrect();
private:
	int state_num;
	int measure_num;

	cv::KalmanFilter KF;
	cv::Mat state;
	cv::Mat process_noise;
	cv::Mat measurement;

	cv::Scalar KF_Q[5];
	cv::Scalar KF_R[5];

	cv::Mat KF_predict;
	cv::Mat KF_correct;
};
