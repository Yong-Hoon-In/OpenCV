#include <opencv/cv.h>
#include <opencv/highgui.h>

int main() {
	IplImage* src_image = 0;
	IplImage* dst_image = 0;

	int height, width,i,j,x,y;
	uchar *data, *data1;
	double mask[3][3]={{0.1111,0.1111,0.1111},
					   {0.1111,0.1111,0.1111},
					   {0.1111,0.1111,0.1111}};
	double tmp;
	src_image = cvLoadImage("lena.jpg", 0);

	height = src_image->height;
	width = src_image->width;
	data = (uchar*)src_image->imageData;
	uchar temp[512][512];

	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Filtered", CV_WINDOW_AUTOSIZE);

	dst_image = cvCreateImage(cvGetSize(src_image), IPL_DEPTH_8U, 1);
	
	data1 = (uchar*)dst_image->imageData;
	
		
			


	for (i = 0; i < height; i++) {
		for ( j = 0; j < width; j++) {
			temp[i][j] = data[i*width + j];
		}
	}
	
	
	
	for ( x = 0; x < height; x++) {
		for ( y = 0; y < width; y++) {
			tmp = 0;
			for ( i = -1; i < 2; i++) {
				for ( j = -1; j < 2; j++) {
					if ((x==0&&i==-1)||(x-1==height&&i==1)||(y==0&&j==-1)||(y-1==width&&j==1))
						tmp+=0;
					else
						tmp += temp[x + i][y + j] *mask[i+1][j+1];
				}
			}
			data1[x * width + y] = (uchar)tmp;

		}
	}



	cvShowImage("Original", src_image);
	cvShowImage("Filtered", dst_image);
	cvWaitKey(0);
	cvReleaseImage(&src_image);
	cvReleaseImage(&dst_image);

}
