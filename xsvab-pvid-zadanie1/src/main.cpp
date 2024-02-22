#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
	cv::Mat image = cv::imread("assets\\Histo_CV2.png");
	cv::imshow("Histology", image);

	cv::waitKey();

	return 0;
}
