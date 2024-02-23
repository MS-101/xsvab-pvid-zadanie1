#include <iostream>
#include <opencv2/opencv.hpp>


void detectObjects(cv::Mat input, cv::Mat processed, int objectSize, int retMode)
{
	cv::Mat output = input.clone();
	int objectCount = 0;

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(processed, contours, retMode, cv::CHAIN_APPROX_SIMPLE);

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

	cv::imshow("output", output);
	std::cout << "Detected " << objectCount << " objects." << std::endl;
}

void countCancerCells()
{
	// input

	cv::Mat input = cv::imread("assets\\Histo_CV2.png");
	cv::resize(input, input, cv::Size(input.cols / 8, input.rows / 8));
	cv::imshow("input", input);

	// preprocessing

	cv::Mat grayscale;
	cv::cvtColor(input, grayscale, cv::COLOR_BGR2GRAY);
	cv::imshow("grayscale", grayscale);

	// binarization

	cv::Mat threshold;
	cv::threshold(grayscale, threshold, 100, 255, cv::THRESH_BINARY);
	cv::bitwise_not(threshold, threshold);
	cv::imshow("threshold", threshold);

	detectObjects(input, threshold, -1, cv::RETR_EXTERNAL);
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

	detectObjects(input, dilate, 50, cv::RETR_CCOMP);
	cv::waitKey();
}

void countBloodCells()
{
	// input

	cv::Mat input = cv::imread("assets\\Red_blood_cells\\img (1).png");
	cv::imshow("original", input);

	//  preprocessing

	cv::Mat grayscale;
	cv::cvtColor(input, grayscale, cv::COLOR_BGR2GRAY);
	cv::imshow("grayscale", grayscale);

	cv::Mat gauss;
	cv::GaussianBlur(grayscale, gauss, cv::Size(5, 5), 0);
	cv::imshow("gauss", gauss);

	// binarization

	cv::Mat threshold;
	cv::threshold(gauss, threshold, 200, 255, cv::THRESH_BINARY);
	cv::bitwise_not(threshold, threshold);
	cv::imshow("threshold", threshold);

	// postprocessing

	cv::Mat erode;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
	cv::erode(threshold, erode, kernel);
	cv::imshow("erode", erode);

	// contour detection

	detectObjects(input, threshold, 20, cv::RETR_EXTERNAL);
	cv::waitKey();
}

int main()
{
	countCancerCells();
	countBeerBubbles();
	countBloodCells();

	return 0;
}
