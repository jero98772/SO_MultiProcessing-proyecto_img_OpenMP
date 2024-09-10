#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

// Function to sum two images
cv::Mat sumImages(const cv::Mat& img1, const cv::Mat& img2) {
    // Check if both images are loaded
    if (img1.empty() || img2.empty()) {
        std::cerr << "Error: One or both images are empty." << std::endl;
        return cv::Mat();
    }

    // Ensure both images have the same type
    if (img1.type() != img2.type()) {
        std::cerr << "Error: Image types do not match." << std::endl;
        return cv::Mat();
    }

    // Get the size of the larger image
    int rows = std::max(img1.rows, img2.rows);
    int cols = std::max(img1.cols, img2.cols);

    // Create a new image with the larger size
    cv::Mat result(rows, cols, img1.type(), cv::Scalar(0, 0, 0));

    // Resize images to match the size of the result
    cv::Mat img1_resized, img2_resized;
    cv::resize(img1, img1_resized, result.size(), 0, 0, cv::INTER_LINEAR);
    cv::resize(img2, img2_resized, result.size(), 0, 0, cv::INTER_LINEAR);

    // Check if resized images are not empty
    if (img1_resized.empty() || img2_resized.empty()) {
        std::cerr << "Error: Resized images are empty." << std::endl;
        return cv::Mat();
    }

    // Add the two images pixel-by-pixel using OpenCV's add function
    cv::add(img1_resized, img2_resized, result);
    return result;
}

int main() {
    // Load the two input images
    cv::Mat img1 = cv::imread("1.png", cv::IMREAD_UNCHANGED);
    cv::Mat img2 = cv::imread("2.png", cv::IMREAD_UNCHANGED);

    // Check if the images were loaded successfully
    if (img1.empty()) {
        std::cerr << "Error: Could not load image 1.png." << std::endl;
        return -1;
    }
    if (img2.empty()) {
        std::cerr << "Error: Could not load image 2.png." << std::endl;
        return -1;
    }

    // Print image types for debugging
    std::cout << "Type of img1: " << img1.type() << std::endl;
    std::cout << "Type of img2: " << img2.type() << std::endl;

    // Call the sumImages function and save the result
    cv::Mat resultImage = sumImages(img1, img2);
    if (!resultImage.empty()) {
        // Save the result image
        if (!cv::imwrite("3.png", resultImage)) {
            std::cerr << "Error: Could not save result image." << std::endl;
            return -1;
        }
        std::cout << "Result image saved successfully." << std::endl;
    } else {
        std::cerr << "Error: Result image is empty." << std::endl;
        return -1;
    }

    return 0;
}