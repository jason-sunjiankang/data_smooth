#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class ShowData
{
public:
	ShowData();
	~ShowData();

public:
	vector<Point3f> m_OriginalDataList;
	vector<Point3f> m_SmoothDataList;

	int m_DataSize;
	Mat m_ShowMat;
	Point3f m_MidData;

public:
	void ShowOriginalData(Point3f pt3f);
	void ShowSmoothData(Point3f pt3f);
	void ShowALLData(Point3f opt3f, Point3f spt3f);

	void ClearData();

private:

};