#include "KalmanFilter.h"


CKalmanFilter::CKalmanFilter()
{
	KF_Q[0] = cv::Scalar::all(1e-1);
	KF_Q[1] = cv::Scalar::all(1e-2);
	KF_Q[2] = cv::Scalar::all(1e-3);
	KF_Q[3] = cv::Scalar::all(1e-4);
	KF_Q[4] = cv::Scalar::all(1e-5);

	KF_R[0] = cv::Scalar::all(1e-1);
	KF_R[1] = cv::Scalar::all(1e-2);
	KF_R[2] = cv::Scalar::all(1e-3);
	KF_R[3] = cv::Scalar::all(1e-4);
	KF_R[4] = cv::Scalar::all(1e-5);

	state_num = 6;
	measure_num = 3;

	KF=cv::KalmanFilter(state_num, measure_num, 0);
	
	state = cv::Mat(state_num,1,CV_32FC1);
	process_noise = cv::Mat(state_num, 1, CV_32FC1);
	measurement = cv::Mat::zeros(measure_num, 1, CV_32FC1);
}

CKalmanFilter::~CKalmanFilter()
{
}

void CKalmanFilter::intKalmanFilter(int &Q, int &R,bool &need_speed)
{
	randn(state, cv::Scalar::all(0), cv::Scalar::all(0.1));

	if (need_speed)
	{
		KF.transitionMatrix = (cv::Mat_<float>(6, 6) <<
			1, 0, 0, 0.85, 0, 0,
			0, 1, 0, 0, 0.85, 0,
			0, 0, 1, 0, 0, 0.85,
			0, 0, 0, 0.85, 0, 0,
			0, 0, 0, 0, 0.85, 0,
			0, 0, 0, 0, 0, 0.85);
	}
	else
	{
		KF.transitionMatrix = (cv::Mat_<float>(6, 6) <<
		1, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0) ;
	}




	cv::setIdentity(KF.measurementMatrix);

	//process noise covariance matrix (Q)
	cv::setIdentity(KF.processNoiseCov, KF_Q[Q-1]);

	//measurement noise covariance matrix (R) 
	cv::setIdentity(KF.measurementNoiseCov, KF_R[R-1]);

	//priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/  A´ú±íF: transitionMatrix
	cv::setIdentity(KF.errorCovPost, cv::Scalar::all(1));

	//corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k)) 
	//initialize post state of kalman filter at random
	randn(KF.statePost, cv::Scalar::all(0), cv::Scalar::all(0.1));

}


void CKalmanFilter::kalmanFilterUpdate(cv::Point3f &src_data)
{
	//2.kalman prediction     
	 KF_predict = KF.predict();

	//3.update measurement  
	measurement.at<float>(0) = src_data.x;
	measurement.at<float>(1) = src_data.y;
	measurement.at<float>(2) = src_data.z;

	//4.update  
	KF_correct = KF.correct(measurement);
}
cv::Point3f CKalmanFilter::getKalmanFilterPredict()
{
	cv::Point3f prediction = cv::Point3f(KF_predict.at<float>(0), KF_predict.at<float>(1), KF_predict.at<float>(2));
	return prediction;
}
cv::Point3f CKalmanFilter::getKalmanFilterCorrect()
{
	cv::Point3f correction = cv::Point3f(KF_correct.at<float>(0), KF_correct.at<float>(1), KF_correct.at<float>(2));
	return correction;
}