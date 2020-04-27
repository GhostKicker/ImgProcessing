#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;


array<int, 256> get_hist(Mat pic) {
    array<int, 256> res;
    fill(res.begin(), res.end(), 0);
    for (int row = 0; row < pic.rows; ++row) {
        for (int col = 0; col < pic.cols; ++col) {
            res[pic.at<uchar>(row, col)]++;
        }
    }
    int mx = *max_element(res.begin(), res.end());
    for (auto& it : res) it = it * 256 / mx;
    return res;
}





int main() {
    Mat pic = imread("unnamed.png");
    cvtColor(pic, pic, COLOR_BGR2GRAY);

    auto hist = get_hist(pic);

    Mat histviz = Mat::zeros(256, 256, CV_8U);
    for (int col = 0; col < (int)hist.size(); ++col) {
        for (int row = 0; row < hist[col]; ++row) {
            histviz.at<uchar>(255 - row, col) = 255;
        }
    }

    array<uchar, 256> lookup;
    for (int i = 0; i < 256; ++i) {
        lookup[i] = abs(255 - 2 * i);
        //lookup[i] = pow(1.0 * i / 256, 2) * 256;
    }
    Mat lookupviz = Mat::zeros(256, 256, CV_8U);
    for (int i = 0; i < (int)lookup.size(); ++i) lookupviz.at<uchar>(255 - lookup[i], i) = 255;

    Mat pic2;
    LUT(pic, lookup, pic2);
    auto hist2 = get_hist(pic2);

    Mat histviz2 = Mat::zeros(256, 256, CV_8U);
    for (int col = 0; col < (int)hist2.size(); ++col) {
        for (int row = 0; row < hist2[col]; ++row) {
            histviz2.at<uchar>(255 - row, col) = 255;
        }
    }


    Mat pic_clahe1, pic_clahe2, pic_clahe3;
    createCLAHE(10, Size(8, 8))->apply(pic, pic_clahe1);
    createCLAHE(10, Size(2, 8))->apply(pic, pic_clahe2);
    createCLAHE(10, Size(8, 2))->apply(pic, pic_clahe3);

    Mat globalbin;
    threshold(pic, globalbin, 80, 255, CV_8U);

    Mat localbin;



    imshow("function", lookupviz);
    imshow("orginal hist", histviz);
    imshow("after func hist", histviz2);
    imshow("original", pic);
    imshow("func", pic2);
    imshow("clahe 10 8 8", pic_clahe1);
    imshow("clahe 10 2 8", pic_clahe2);
    imshow("clahe 10 8 2", pic_clahe3);
    imshow("global binarization", globalbin);


    waitKey(0);
}