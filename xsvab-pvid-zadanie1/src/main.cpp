#include <iostream>
#include <opencv2/opencv.hpp>


void countCancerCells()
{
	cv::Mat image = cv::imread("assets\\Histo_CV2.png");
	cv::imshow("original", image);

	cv::waitKey();
}

void countBeerBubbles()
{
	// input

	cv::Mat input = cv::imread("assets\\pena.tif");
	cv::resize(input, input, cv::Size(input.cols / 8, input.rows / 8));
	cv::imshow("input", input);

	// preprocessing

	cv::Mat gauss;
	cv::GaussianBlur(input, gauss, cv::Size(5, 5), 0);
	cv::imshow("gauss", gauss);

	// binarization

	cv::Mat canny;
	cv::Canny(gauss, canny, 20, 80);
	cv::imshow("canny", canny);

	// postprocessing

	cv::Mat dilate;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
	cv::dilate(canny, dilate, kernel);
	cv::imshow("dilate", dilate);

	// contour detection

	cv::Mat output = input.clone();
	int objectSize = 50;
	int objectCount = 0;

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(dilate, contours, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); ++i) {
		std::vector<cv::Point> points = contours[i];

		if (cv::contourArea(points) > objectSize) {
			objectCount++;

			double centerX = 0.0;
			double centerY = 0.0;

			for (cv::Point point : points) {
				centerX += point.x;
				centerY += point.y;
			}

			centerX /= points.size();
			centerY /= points.size();

			int fontFace = cv::FONT_HERSHEY_PLAIN;
			double fontScale = 0.5;
			cv::Point fontPoint = cv::Point(centerX, centerY);
			cv::Scalar color = cv::Scalar(0, 0, 255);

			cv::putText(output, std::to_string(objectCount), fontPoint, fontFace, fontScale, color);
			cv::drawContours(output, contours, i, color);
		}
	}

	// output

	cv::imshow("output", output);
	std::cout << "Detected " << objectCount << " beer bubbles." << std::endl;
	cv::waitKey();
}

void countBloodCells()
{
	cv::Mat image = cv::imread("assets\\Red_blood_cells\\img (1).png");
	cv::imshow("original", image);

	cv::waitKey();
}

int main()
{
	//countCancerCells();
	countBeerBubbles();
	//countBloodCells();

	return 0;
}
