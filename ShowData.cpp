#include "ShowData.h"

ShowData::ShowData()
{
	m_DataSize = 100;
	m_ShowMat = Mat(900, 1000, CV_8UC3);
}

ShowData::~ShowData()
{

}

void ShowData::ClearData()
{
	m_OriginalDataList.clear();
	m_SmoothDataList.clear();
}

void ShowData::ShowALLData(Point3f opt3f, Point3f spt3f)
{

	//Mat showMat = Mat(900, 1000, CV_8UC3);

	Mat& showMat = m_ShowMat;
	showMat.setTo(160);

	if (m_OriginalDataList.size() < m_DataSize)
	{
		m_OriginalDataList.push_back(opt3f);
		m_SmoothDataList.push_back(spt3f);
	}
	else
	{
		m_OriginalDataList.erase(m_OriginalDataList.begin());
		m_OriginalDataList.push_back(opt3f);

		m_SmoothDataList.erase(m_SmoothDataList.begin());
		m_SmoothDataList.push_back(spt3f);
	}

	float maxData[3] = { -100000, -100000, -100000 };
	float minData[3] = { 100000, 100000, 100000 };

	for (size_t i = 0; i < m_OriginalDataList.size(); i++)
	{
		if (m_OriginalDataList[i].x > maxData[0])
		{
			maxData[0] = m_OriginalDataList[i].x;
		}
		if (m_OriginalDataList[i].y > maxData[1])
		{
			maxData[1] = m_OriginalDataList[i].y;
		}
		if (m_OriginalDataList[i].z > maxData[2])
		{
			maxData[2] = m_OriginalDataList[i].z;
		}

		if (m_OriginalDataList[i].x < minData[0])
		{
			minData[0] = m_OriginalDataList[i].x;
		}
		if (m_OriginalDataList[i].y < minData[1])
		{
			minData[1] = m_OriginalDataList[i].y;
		}
		if (m_OriginalDataList[i].z < minData[2])
		{
			minData[2] = m_OriginalDataList[i].z;
		}

	}
	Point3f &midData = m_MidData;
	midData.x = minData[0] + (maxData[0] - minData[0]) / 2;
	midData.y = minData[1] + (maxData[1] - minData[1]) / 2;
	midData.z = minData[2] + (maxData[2] - minData[2]) / 2;

	vector<Point3f> originalDataList;
	int istep = 150;
	for (size_t i = 0; i < m_OriginalDataList.size(); i++)
	{
		Point3f pt = m_OriginalDataList[i] - midData;

		if (abs(pt.x) > istep)
		{
			if (pt.x > istep)
			{
				pt.x = istep;
			}
			else
			{
				pt.x = -istep;
			}

		}

		if (abs(pt.y) > istep)
		{
			if (pt.y > istep)
			{
				pt.y = istep;
			}
			else
			{
				pt.y = -istep;
			}

		}

		if (abs(pt.z) > istep)
		{
			if (pt.z > istep)
			{
				pt.z = istep;
			}
			else
			{
				pt.z = -istep;
			}

		}

		originalDataList.push_back(pt);
	}

	vector<Point3f> smoothDataList;
	for (size_t i = 0; i < m_SmoothDataList.size(); i++)
	{
		Point3f pt = m_SmoothDataList[i] - midData;

		if (abs(pt.x) > istep)
		{
			if (pt.x > istep)
			{
				pt.x = istep;
			}
			else
			{
				pt.x = -istep;
			}

		}

		if (abs(pt.y) > istep)
		{
			if (pt.y > istep)
			{
				pt.y = istep;
			}
			else
			{
				pt.y = -istep;
			}

		}

		if (abs(pt.z) > istep)
		{
			if (pt.z > istep)
			{
				pt.z = istep;
			}
			else
			{
				pt.z = -istep;
			}

		}

		smoothDataList.push_back(pt);
	}

	line(showMat, Point(0, istep), Point(1000, istep), Scalar(0, 0, 0));
	line(showMat, Point(0, istep * 3), Point(1000, istep * 3), Scalar(0, 0, 0));
	line(showMat, Point(0, istep * 5), Point(1000, istep * 5), Scalar(0, 0, 0));

	Point pt1, pt2;
	for (size_t i = 1; i < originalDataList.size(); i++)
	{
		pt1 = Point((i - 1) * 10, originalDataList[i - 1].x + istep);
		pt2 = Point(i * 10, originalDataList[i].x + istep);
		line(showMat, pt1, pt2, Scalar(0, 0, 255));

		pt1 = Point((i - 1) * 10, originalDataList[i - 1].y + istep * 3);
		pt2 = Point(i * 10, originalDataList[i].y + istep * 3);
		line(showMat, pt1, pt2, Scalar(0, 0, 255));

		pt1 = Point((i - 1) * 10, originalDataList[i - 1].z + istep * 5);
		pt2 = Point(i * 10, originalDataList[i].z + istep * 5);
		line(showMat, pt1, pt2, Scalar(0, 0, 255));

	}

	for (size_t i = 1; i < smoothDataList.size(); i++)
	{
		pt1 = Point((i - 1) * 10, smoothDataList[i - 1].x + istep);
		pt2 = Point(i * 10, smoothDataList[i].x + istep);
		line(showMat, pt1, pt2, Scalar(0, 255, 0));

		pt1 = Point((i - 1) * 10, smoothDataList[i - 1].y + istep * 3);
		pt2 = Point(i * 10, smoothDataList[i].y + istep * 3);
		line(showMat, pt1, pt2, Scalar(0, 255, 0));

		pt1 = Point((i - 1) * 10, smoothDataList[i - 1].z + istep * 5);
		pt2 = Point(i * 10, smoothDataList[i].z + istep * 5);
		line(showMat, pt1, pt2, Scalar(0, 255, 0));

	}


	imshow("ShowData", showMat);
	waitKey(1);

}

void ShowData::ShowOriginalData(Point3f pt3f)
{
	Mat showMat = Mat(900, 1000, CV_8UC3);
	showMat.setTo(160);

	if (m_OriginalDataList.size() < m_DataSize)
	{
		m_OriginalDataList.push_back(pt3f);
	}
	else
	{
		m_OriginalDataList.erase(m_OriginalDataList.begin());
		m_OriginalDataList.push_back(pt3f);
	}

	float maxData[3] = { -100000, -100000, -100000 };
	float minData[3] = { 100000, 100000, 100000 };
	
	for (size_t i = 0; i < m_OriginalDataList.size(); i++)
	{
		if (m_OriginalDataList[i].x > maxData[0])
		{
			maxData[0] = m_OriginalDataList[i].x;
		}
		if (m_OriginalDataList[i].y > maxData[1])
		{
			maxData[1] = m_OriginalDataList[i].y;
		}
		if (m_OriginalDataList[i].z > maxData[2])
		{
			maxData[2] = m_OriginalDataList[i].z;
		}

		if (m_OriginalDataList[i].x < minData[0])
		{
			minData[0] = m_OriginalDataList[i].x;
		}
		if (m_OriginalDataList[i].y < minData[1])
		{
			minData[1] = m_OriginalDataList[i].y;
		}
		if (m_OriginalDataList[i].z < minData[2])
		{
			minData[2] = m_OriginalDataList[i].z;
		}

	}
	Point3f &midData = m_MidData;
	midData.x = minData[0] + (maxData[0] - minData[0]) / 2;
	midData.y = minData[1] + (maxData[1] - minData[1]) / 2;
	midData.z = minData[2] + (maxData[2] - minData[2]) / 2;

	vector<Point3f> originalDataList;
	int istep = 150;
	for (size_t i = 0; i < m_OriginalDataList.size(); i++)
	{
		Point3f pt = m_OriginalDataList[i] - midData;

		if (abs(pt.x) > istep)
		{
			if (pt.x > istep)
			{
				pt.x = istep;
			}
			else
			{
				pt.x = -istep;
			}

		}

		//pt.x += 100;

		if (abs(pt.y) > istep)
		{
			if (pt.y > istep)
			{
				pt.y = istep;
			}
			else
			{
				pt.y = -istep;
			}

		}

		//pt.y += 300;

		if (abs(pt.z) > istep)
		{
			if (pt.z > istep)
			{
				pt.z = istep;
			}
			else
			{
				pt.z = -istep;
			}

		}

		//pt.z += 500;

		originalDataList.push_back(pt);
	}

	line(showMat, Point(0, istep), Point(1000, istep), Scalar(0, 0, 0));
	line(showMat, Point(0, istep * 3), Point(1000, istep*3), Scalar(0, 0, 0));
	line(showMat, Point(0, istep * 5), Point(1000, istep*5), Scalar(0, 0, 0));

	Point pt1, pt2;
	for (size_t i = 1; i < originalDataList.size(); i++)
	{
		pt1 = Point((i - 1) * 10, originalDataList[i - 1].x + istep);
		pt2 = Point(i * 10, originalDataList[i].x + istep);
		line(showMat, pt1, pt2, Scalar(0, 0, 255));

		pt1 = Point((i - 1) * 10, originalDataList[i - 1].y + istep*3);
		pt2 = Point(i * 10, originalDataList[i].y + istep*3);
		line(showMat, pt1, pt2, Scalar(0, 0, 255));

		pt1 = Point((i - 1) * 10, originalDataList[i - 1].z + istep*5);
		pt2 = Point(i * 10, originalDataList[i].z + istep*5);
		line(showMat, pt1, pt2, Scalar(0,0,  255));

	}


	imshow("OriginalData", showMat);
	waitKey(1);
}


void ShowData::ShowSmoothData(Point3f pt3f)
{
	Mat showMat = Mat(900, 1000, CV_8UC3);
	showMat.setTo(160);

	if (m_SmoothDataList.size() < m_DataSize)
	{
		m_SmoothDataList.push_back(pt3f);
	}
	else
	{
		m_SmoothDataList.erase(m_SmoothDataList.begin());
		m_SmoothDataList.push_back(pt3f);
	}

	float maxData[3] = { -100000, -100000, -100000 };
	float minData[3] = { 100000, 100000, 100000 };

	for (size_t i = 0; i < m_SmoothDataList.size(); i++)
	{
		if (m_SmoothDataList[i].x > maxData[0])
		{
			maxData[0] = m_SmoothDataList[i].x;
		}
		if (m_SmoothDataList[i].y > maxData[1])
		{
			maxData[1] = m_SmoothDataList[i].y;
		}
		if (m_SmoothDataList[i].z > maxData[2])
		{
			maxData[2] = m_SmoothDataList[i].z;
		}

		if (m_SmoothDataList[i].x < minData[0])
		{
			minData[0] = m_SmoothDataList[i].x;
		}
		if (m_SmoothDataList[i].y < minData[1])
		{
			minData[1] = m_SmoothDataList[i].y;
		}
		if (m_SmoothDataList[i].z < minData[2])
		{
			minData[2] = m_SmoothDataList[i].z;
		}

	}
	Point3f midData;
	midData.x = minData[0] + (maxData[0] - minData[0]) / 2;
	midData.y = minData[1] + (maxData[1] - minData[1]) / 2;
	midData.z = minData[2] + (maxData[2] - minData[2]) / 2;

	vector<Point3f> smoothDataList;
	int istep = 150;
	for (size_t i = 0; i < m_SmoothDataList.size(); i++)
	{
		Point3f pt = m_SmoothDataList[i] - midData;

		if (abs(pt.x) > istep)
		{
			if (pt.x > istep)
			{
				pt.x = istep;
			}
			else
			{
				pt.x = -istep;
			}

		}

		//pt.x += 100;

		if (abs(pt.y) > istep)
		{
			if (pt.y > istep)
			{
				pt.y = istep;
			}
			else
			{
				pt.y = -istep;
			}

		}

		//pt.y += 300;

		if (abs(pt.z) > istep)
		{
			if (pt.z > istep)
			{
				pt.z = istep;
			}
			else
			{
				pt.z = -istep;
			}

		}

		//pt.z += 500;

		smoothDataList.push_back(pt);
	}

	line(showMat, Point(0, istep), Point(1000, istep), Scalar(0, 0, 0));
	line(showMat, Point(0, istep * 3), Point(1000, istep * 3), Scalar(0, 0, 0));
	line(showMat, Point(0, istep * 5), Point(1000, istep * 5), Scalar(0, 0, 0));

	Point pt1, pt2;
	for (size_t i = 1; i < smoothDataList.size(); i++)
	{
		pt1 = Point((i - 1) * 10, smoothDataList[i - 1].x + istep);
		pt2 = Point(i * 10, smoothDataList[i].x + istep);
		line(showMat, pt1, pt2, Scalar(0, 255, 0));

		pt1 = Point((i - 1) * 10, smoothDataList[i - 1].y + istep * 3);
		pt2 = Point(i * 10, smoothDataList[i].y + istep * 3);
		line(showMat, pt1, pt2, Scalar(0, 255, 0));

		pt1 = Point((i - 1) * 10, smoothDataList[i - 1].z + istep * 5);
		pt2 = Point(i * 10, smoothDataList[i].z + istep * 5);
		line(showMat, pt1, pt2, Scalar(0,255,  0));

	}


	imshow("smoothData", showMat);
	waitKey(1);
}