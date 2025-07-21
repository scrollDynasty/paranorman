#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;
using namespace cv;

string pixelToASCII(int pixel_intensity) {
    const string ASCII_CHARS = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    string s = string(1, ASCII_CHARS[pixel_intensity * ASCII_CHARS.length() / 256]);
    return s;
}

int main() {
    string image_path = "/home/whoami/coding/paranorman/Mitch_Downe.jpg"; 
    
    Mat image = imread(image_path);

    if (image.empty()) {
        cerr << "Error: Failed to load image at path: " << image_path << endl;
        return -1;
    }

    int width = 120; 
    
    int frame_width = image.cols;
    int frame_height = image.rows;
    double aspectRatioCorrection = 0.5; 

    int height = static_cast<int>((static_cast<double>(width) * frame_height / frame_width) * aspectRatioCorrection); 

    Mat gray_frame, resized_frame;

    cv::cvtColor(image, gray_frame, cv::COLOR_BGR2GRAY);

    resize(gray_frame, resized_frame, Size(width, height), 0, 0, INTER_LINEAR);

    string ascii_frame;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ascii_frame += pixelToASCII(resized_frame.at<uchar>(i, j));
        }
        ascii_frame += "\n";
    }

    system("clear"); 
    cout << ascii_frame;

    cout << "\nPress Enter to output...";
    cin.get(); 

    return 0;
}