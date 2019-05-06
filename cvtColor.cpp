#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main()
{
	Mat srcImg = imread("15.jpg");
	if (srcImg.empty())
		return -1;

	Mat grayImg;
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
	imshow("gray", grayImg);
	Mat hsvImg;
	cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);
	imshow("hsv", hsvImg);
	Mat yCbcrImg;
	cvtColor(srcImg, yCbcrImg, COLOR_BGR2YCrCb);
	imshow("ycb", yCbcrImg);
	Mat luvImg;
	cvtColor(srcImg, luvImg, COLOR_BGR2Luv);
	imshow("luv", luvImg);
	waitKey();

	return 0;
}
