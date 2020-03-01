#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

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
    for (int col = 0; col < hist.size(); ++col) {
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
    for (int i = 0; i < lookup.size(); ++i) lookupviz.at<uchar>(255 - lookup[i], i) = 255;

    Mat pic2;
    LUT(pic, lookup, pic2);
    auto hist2 = get_hist(pic2);

    Mat histviz2 = Mat::zeros(256, 256, CV_8U);
    for (int col = 0; col < hist2.size(); ++col) {
        for (int row = 0; row < hist2[col]; ++row) {
            histviz2.at<uchar>(255 - row, col) = 255;
        }
    }
    Mat piceq;
    equalizeHist(pic, piceq);


    imshow("function", lookupviz);
    imshow("orginal hist", histviz);
    imshow("after func hist", histviz2);
    imshow("original", pic);
    imshow("equalized", piceq);
    imshow("func", pic2);
    waitKey(0);
}