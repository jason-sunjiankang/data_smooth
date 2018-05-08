#include<opencv2/opencv.hpp>


class CAverageFilter
{
public:
	CAverageFilter();
	~CAverageFilter();
	cv::Point3f averageFilter(cv::Point3f &src_data);

private:
	cv::Point3f getMeanData(cv::vector<cv::Point3f>  &data_list);
	cv::Point3f mean_data;
	
	int thread_value;

	cv::vector<cv::Point3f> data_list_move;
	cv::vector<cv::Point3f> data_list_static;

	int total_static_num;
	int total_move_num;
};