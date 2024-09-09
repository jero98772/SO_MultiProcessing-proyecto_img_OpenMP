#include <opencv2/opencv.hpp>
#include <cmath>

// Function to rotate the image by a given angle
cv::Mat rotate_image(const cv::Mat& image, double angle) {
    double angle_rad = angle * CV_PI / 180.0; // Convert angle to radians
    double cos_angle = std::cos(angle_rad);
    double sin_angle = std::sin(angle_rad);
    
    // Get original image dimensions
    int h = image.rows;
    int w = image.cols;
    
    // Compute the new dimensions
    int new_h = static_cast<int>(std::abs(h * cos_angle) + std::abs(w * sin_angle));
    int new_w = static_cast<int>(std::abs(w * cos_angle) + std::abs(h * sin_angle));
    
    // Create the output image
    cv::Mat rotated_image = cv::Mat::zeros(new_h, new_w, image.type());
    
    // Find the center of the old and new images
    cv::Point2f center_old(w / 2.0f, h / 2.0f);
    cv::Point2f center_new(new_w / 2.0f, new_h / 2.0f);
    
    // Iterate over every pixel in the new image
    for (int y = 0; y < new_h; ++y) {
        for (int x = 0; x < new_w; ++x) {
            // Translate the pixel to the origin
            cv::Point2f pixel(x, y);
            pixel -= center_new;
            
            // Rotate the pixel
            int old_x = static_cast<int>(pixel.x * cos_angle + pixel.y * sin_angle + center_old.x);
            int old_y = static_cast<int>(-pixel.x * sin_angle + pixel.y * cos_angle + center_old.y);
            
            // If the pixel is within the bounds of the old image, copy the pixel value
            if (0 <= old_x && old_x < w && 0 <= old_y && old_y < h) {
                rotated_image.at<cv::Vec3b>(y, x) = image.at<cv::Vec3b>(old_y, old_x);
            }
        }
    }
    
    return rotated_image;
}

int main() {
    // Load an image from a file
    cv::Mat image = cv::imread("1.png");

    // Check if the image was successfully loaded
    if (image.empty()) {
        std::cerr << "Error: Unable to load image." << std::endl;
        return -1;
    }

    // Rotate the image by 145 degrees
    cv::Mat rotated_image = rotate_image(image, 145);

    // Display the rotated image
    cv::imshow("Rotated Image", rotated_image);
    cv::waitKey(0);  // Wait for a key press to close the window
    cv::destroyAllWindows();
    
    return 0;
}
