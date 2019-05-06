#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main()
{
	Mat srcImg = imread("15.jpg");
	if (srcImg.empty())
		return -1;

	Mat hsvImg;
	cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);
	vector<Mat> planes;
	split(hsvImg, planes);
	Mat hueImg = planes[0];
	Rect roi(100, 100, 100, 100);
	rectangle(srcImg, roi, Scalar(0, 0, 255), 2);
	Mat roiImg = hueImg(roi);
	int histSize = 256;
	float hValue[] = { 0,256 };
	const float* ranges[] = { hValue };
	int channels = 0;
	int dims = 1;
	Mat hist;
	calcHist(&roiImg, 1, &channels, Mat(), hist, dims, &histSize, ranges);		//역투영,관심영역히스토리
	Mat hueImg2;
	hueImg.convertTo(hueImg2, CV_32F);
	Mat backProject;
	calcBackProject(&hueImg2, 1, &channels, hist, backProject, ranges);
	double minVal, maxVal;
	minMaxLoc(backProject, &minVal, &maxVal);
	cout << minVal << endl;
	cout << maxVal << endl;
	Mat backProject2;
	normalize(backProject, backProject2, 0, 255, NORM_MINMAX, CV_8U);
	imshow("backPt2", backProject2);
	imshow("src", srcImg);
	waitKey();
	

	return 0;
}

