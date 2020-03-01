#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    int h = 60;
    int w = 3 * 256;
    Mat img(Mat::zeros(h, w, CV_8U));
    Mat imgres(Size(w, 2 * h), CV_8U);
    for (int col = 0; col < w; ++col) {
        for (int row = 0; row < h; ++row) {
            img.at<uchar>(Point(col, row)) = 5 + col / 30 * 10;
        }
    }
    img.copyTo(imgres(Rect(0, 0, w, h)));
    img.convertTo(img, CV_64F, 1.0 / 256);
    cv::pow(img, 2.3, img);
    img.convertTo(img, CV_8U, 256);
    img.copyTo(imgres(Rect(0, h, w, h)));


    namedWindow("a", 1);
    imshow("a", imgres);
    waitKey(0);



}