#include "AverageFilter.h"


CAverageFilter::CAverageFilter()
{
	mean_data = cv::Point3f(0.0,0.0,0.0);
	thread_value = 10;

	total_static_num = 30;
	total_move_num = 50;
}

CAverageFilter::~CAverageFilter()
{

}



cv::Point3f CAverageFilter::getMeanData(cv::vector<cv::Point3f>  &data_list)
{
	cv::Point3f data;
	for (size_t i = 0; i < data_list.size(); i++)
	{
		data.x += data_list[i].x;
		data.y += data_list[i].y;
		data.z += data_list[i].z;
	}

	data.x /= data_list.size();
	data.y /= data_list.size();
	data.z /= data_list.size();

	return data;

}


cv::Point3f CAverageFilter::averageFilter(cv::Point3f &src_data)
{

	float distance = sqrtf((mean_data.x - src_data.x) *(mean_data.x - src_data.x)
		+ (mean_data.y - src_data.y) *(mean_data.y - src_data.y)
		+ (mean_data.z - src_data.z) *(mean_data.z - src_data.z));

	/*if the distance between point(x1,y1) and point (x0,y0) less than thread_value,we thought the point static,then storage the data into data_list_static,caculate the mean data
	if the distance between point(x1, y1) and point(x0, y0) more than thread_value, we thought the point moved, then storage the data into data_list_move,caculate the mean data*/
	if (distance < thread_value)
	{
		data_list_move.clear();

		if (data_list_static.size() == total_static_num)
		{
			data_list_static.erase(data_list_static.begin());
		}
		else
		{
			data_list_static.push_back(src_data);
		}
		    
		mean_data = getMeanData(data_list_static);
	}
	else
	{
		data_list_static.clear();

		if (data_list_move.size() == total_move_num)
		{
			data_list_move.erase(data_list_move.begin());
		}
		data_list_move.push_back(src_data);
		mean_data = getMeanData(data_list_move);
	}

	return mean_data;

}