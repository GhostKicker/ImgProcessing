#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace cv;

int8_t mydata[3][3] = { {1, 0, -1},{2, 0, -2},{1, 0, -1} };
int8_t mydatat[3][3] = { {1, 2, 1},{0, 0, 0},{-1, -2, -1} };

int rows = 200;
int cols = 200;
void go_filter(Mat& pic, Mat& resf, Mat& filter) {
    for (int c = 1; c + 1 < 3 * cols; ++c) {
        for (int r = 1; r + 1 < 2 * rows; ++r) {
            int tmpf = 0;
            for (int cc = 0; cc < 3; ++cc) {
                for (int rr = 0; rr < 3; ++rr) {
                    tmpf += 1 * filter.at<int8_t>(Size(cc, rr)) * pic.at<uchar>(Size(c + cc - 1, r + rr - 1));
                }
            }
            tmpf += 4 * 255;
            tmpf /= 2;
            if (tmpf > 255) tmpf = 255;
            if (tmpf < 0) tmpf = 0;
            resf.at<uchar>(Size(c, r)) = tmpf;
        }
    }

}
void cool_filter(Mat& pic, Mat& resf, Mat& filter, Mat& filtert) {
    for (int c = 1; c + 1 < 3 * cols; ++c) {
        for (int r = 1; r + 1 < 2 * rows; ++r) {
            int tmpf = 0;
            int tmpft = 0;
            for (int cc = 0; cc < 3; ++cc) {
                for (int rr = 0; rr < 3; ++rr) {
                    tmpf += 1 * filter.at<int8_t>(Size(cc, rr)) * pic.at<uchar>(Size(c + cc - 1, r + rr - 1));
                    tmpft += 1 * filtert.at<int8_t>(Size(cc, rr)) * pic.at<uchar>(Size(c + cc - 1, r + rr - 1));
                }
            }
            int res = 0;
            res += tmpf * tmpf;
            res += tmpft * tmpft;
            res = sqrt(res);
            res /= 2;
            res /= sqrt(2);
            res += 127;
            if (res > 255) res = 255;
            if (res < 0) res = 0;
            resf.at<uchar>(Size(c, r)) = res;
        }
    }

}




int main() {
    Mat pic = Mat::zeros(Size(3 * cols, 2 * rows), CV_8U);

    vector<uchar> colors = { 0, 128, 255 };
    for (int c = 0; c < 3; ++c) {
        for (int r = 0; r < 2; ++r) {
            Mat cur(Size(cols, rows), CV_8U);
            int ind = (r + c) % 3;
            int cind = (ind - 1 + 2 * r + 3) % 3;
            cur.setTo(Scalar(1, 1, 1) * colors[ind]);
            circle(cur, Point(cols / 2, rows / 2), 50, Scalar(1, 1, 1) * colors[cind], -1);
            cur.copyTo(pic(Rect(c * cols, r * rows, cols, rows)));
        }
    }

    Mat filter(Size(3, 3), CV_8S, &mydata);
    Mat filtert(Size(3, 3), CV_8S, &mydatat);
    cout << filter << endl;
    Mat resf(Size(3 * cols, 2 * rows), CV_8U);
    Mat resft(Size(3 * cols, 2 * rows), CV_8U);
    Mat resfft(Size(3 * cols, 2 * rows), CV_8U);

    //filter2D(pic(Rect(1, 1, 3 * cols - 2, 2 * rows - 2)), resf, 0, filter, Point(-1, -1), BORDER_DEFAULT);
    go_filter(pic, resf, filter);
    go_filter(pic, resft, filtert);
    cool_filter(pic, resfft, filter, filtert);

    imshow("a", pic);

    imshow("b", resf);
    imshow("c", resft);
    imshow("d", resfft);

    waitKey(0);


}