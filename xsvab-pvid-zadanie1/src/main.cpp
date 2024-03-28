#include <iostream>
#include <opencv2/opencv.hpp>


void outputImage(cv::Mat image, std::string name, std::string dir, std::string extension)
{
	cv::imshow(name, image);
	cv::imwrite(dir + name + extension, image);
}

void detectObjects(cv::Mat input, cv::Mat processed, double objectSize, int retMode, bool useLabels, std::string outputDir, std::string outputExtension)
{
	cv::Mat output = input.clone();
	int objectCount = 0;

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(processed, contours, retMode, cv::CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); ++i) {
		std::vector<cv::Point> points = contours[i];
		cv::Scalar color = cv::Scalar(0, 0, 255);

		if (cv::contourArea(points) > objectSize) {
			objectCount++;

			if (useLabels)
			{
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
				cv::Scalar fontColor = cv::Scalar(0, 0, 255);
				
				cv::putText(output, std::to_string(objectCount), fontPoint, fontFace, fontScale, fontColor);
			}

			cv::drawContours(output, contours, i, color);
		}
	}

	outputImage(output, "output", outputDir, outputExtension);
	std::cout << "Detected " << objectCount << " objects." << std::endl;
}

void countCancerCells()
{
	std::string inputPath = "assets\\Histo_CV2.png";
	std::string outputDir = "output\\cancerCells\\";
	std::string outputExtension = ".png";

	// input

	cv::Mat input = cv::imread(inputPath);
	cv::resize(input, input, cv::Size(input.cols / 8, input.rows / 8));
	outputImage(input, "input", outputDir, outputExtension);

	// preprocessing

	std::vector<cv::Mat> channels;
	cv::split(input, channels);

	cv::Mat red = channels[2];
	outputImage(red, "red", outputDir, outputExtension);

	// binarization

	cv::Mat threshold;
	cv::threshold(red, threshold, 215, 255, cv::THRESH_BINARY);
	cv::bitwise_not(threshold, threshold);
	outputImage(threshold, "threshold", outputDir, outputExtension);

	// contour detection

	detectObjects(input, threshold, 0, cv::RETR_EXTERNAL, false, outputDir, outputExtension);
	cv::waitKey();
}

void countBeerBubbles()
{
	std::string inputPath = "assets\\pena.tif";
	std::string outputDir = "output\\beerBubbles\\";
	std::string outputExtension = ".png";

	// input

	cv::Mat input = cv::imread(inputPath);
	cv::resize(input, input, cv::Size(input.cols / 8, input.rows / 8));
	outputImage(input, "input", outputDir, outputExtension);

	// preprocessing

	cv::Mat grayscale;
	cv::cvtColor(input, grayscale, cv::COLOR_BGR2GRAY);
	outputImage(grayscale, "grayscale", outputDir, outputExtension);

	// binarization

	cv::Mat canny;
	cv::Canny(grayscale, canny, 60, 80);
	outputImage(canny, "canny", outputDir, outputExtension);

	// postprocessing

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(6, 6));

	cv::Mat dilate;
	cv::dilate(canny, dilate, kernel);
	outputImage(dilate, "dilate", outputDir, outputExtension);

	cv::Mat erode;
	cv::erode(dilate, erode, kernel);
	outputImage(erode, "erode", outputDir, outputExtension);

	// contour detection

	detectObjects(input, erode, 50, cv::RETR_CCOMP, true, outputDir, outputExtension);
	cv::waitKey();
}

void countBloodCells()
{
	std::string inputPath = "assets\\Red_blood_cells\\img (1).png";
	std::string outputDir = "output\\bloodCells\\";
	std::string outputExtension = ".png";

	// input

	cv::Mat input = cv::imread(inputPath);
	outputImage(input, "input", outputDir, outputExtension);

	//  preprocessing

	std::vector<cv::Mat> channels;
	cv::split(input, channels);

	cv::Mat green = channels[1];
	outputImage(green, "green", outputDir, outputExtension);

	cv::Mat gauss;
	cv::GaussianBlur(green, gauss, cv::Size(5, 5), 0);
	outputImage(gauss, "gauss", outputDir, outputExtension);

	// binarization

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));

	cv::Mat allBloodCells;
	cv::threshold(gauss, allBloodCells, 200, 255, cv::THRESH_BINARY);
	cv::bitwise_not(allBloodCells, allBloodCells);
	outputImage(allBloodCells, "allBloodCells", outputDir, outputExtension);

	cv::Mat whiteBloodCells;
	cv::threshold(gauss, whiteBloodCells, 150, 255, cv::THRESH_BINARY);
	cv::bitwise_not(whiteBloodCells, whiteBloodCells);
	cv::dilate(whiteBloodCells, whiteBloodCells, kernel);
	outputImage(whiteBloodCells, "whiteBloodCells", outputDir, outputExtension);

	cv::Mat redBloodCells;
	cv::subtract(allBloodCells, whiteBloodCells, redBloodCells);
	outputImage(redBloodCells, "redBloodCells", outputDir, outputExtension);

	// postprocessing

	cv::Mat erode;
	cv::erode(redBloodCells, erode, kernel);
	outputImage(erode, "erode", outputDir, outputExtension);

	// contour detection

	detectObjects(input, erode, 100, cv::RETR_EXTERNAL, true, outputDir, outputExtension);
	cv::waitKey();
}

int main()
{
	countCancerCells();
	countBeerBubbles();
    countBloodCells();

	return 0;
}
