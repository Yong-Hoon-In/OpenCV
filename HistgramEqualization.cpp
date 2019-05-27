#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
#define L 256
void histogram(const char* w_name, Mat img);
int main()
{
	Mat srcImg = imread("15.jpg");
	if (srcImg.empty())
		return -1;
	int histSize[] = { L };
	float valueRange[] = { 0,L };
	const float* ranges[] = { valueRange };
	int channels[] = {0};
	int dims=1;
	Mat hist;
	calcHist(&srcImg, 1, channels, Mat(), hist, dims, histSize, ranges, true);
	Mat pdf;
	normalize(hist, pdf, L - 1, 0, NORM_L1);
	Mat cdf(pdf.size(), pdf.type());
	cdf.at<float>(0) = pdf.at<float>(0);
	for (int i = 1; i < pdf.rows; i++)
		cdf.at<float>(i) = cdf.at<float>(i - 1) + pdf.at<float>(i);
	Mat table(cdf.size(), CV_8U);
	table.at<uchar>(0) = 0;
	for (int i = 1; i < pdf.rows; i++)
		table.at<uchar>(i) = cvRound(cdf.at<float>(i));
	Mat dstImg;

	LUT(srcImg, table, dstImg);
	vector<int> params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(100);
	imwrite("imageEq1.jpg", dstImg, params);
	imshow("beforeImg", srcImg);
	histogram("beforeHist", srcImg);
	imshow("afterImg", dstImg);
	histogram("after", dstImg);
	waitKey();


	return 0;
}
void histogram(const char* w_name, Mat img)
{
	int hist[256] = { 0, };
	double scale = 1;
	int i, j, max = 0;

	Mat canvas(256, 256, CV_8UC1, Scalar(255));

	for (i = 0; i < img.rows; i++)
		for (j = 0; j < img.cols; j++)
			hist[img.at<uchar>(i, j)]++;

	for (i = 0; i < 256; i++)
		max = hist[i] > max ? hist[i] : max;

	max += 10;

	scale = max > canvas.rows ? (double)canvas.rows / max : 1;

	for (i = 0; i < 256; i++)
	{
		Point pt1 = Point(i, canvas.rows - (hist[i] * scale));
		Point pt2 = Point(i, canvas.rows);
		line(canvas, pt1, pt2, Scalar(0));
	}

	imshow(w_name, canvas);
}
