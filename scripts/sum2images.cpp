#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat sumImages(const cv::Mat& img1, const cv::Mat& img2) {
    // Get the size of the larger image
    int rows = std::max(img1.rows, img2.rows);
    int cols = std::max(img1.cols, img2.cols);

    // Create a new image with the larger size
    cv::Mat result(rows, cols, img1.type());

    // Add the two images pixel-by-pixel
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            cv::Vec3b pixel1 = (y < img1.rows && x < img1.cols) ? img1.at<cv::Vec3b>(y, x) : cv::Vec3b(0, 0, 0);
            cv::Vec3b pixel2 = (y < img2.rows && x < img2.cols) ? img2.at<cv::Vec3b>(y, x) : cv::Vec3b(0, 0, 0);
            result.at<cv::Vec3b>(y, x) = pixel1 + pixel2;
        }
    }

    return result;
}

int main() {
    // Load the two input images
    cv::Mat img1 = cv::imread("image1.jpg");
    cv::Mat img2 = cv::imread("image2.jpg");

    // Call the sumImages function and save the result
    cv::Mat resultImage = sumImages(img1, img2);
    cv::imwrite("result_image.jpg", resultImage);

    return 0;
}