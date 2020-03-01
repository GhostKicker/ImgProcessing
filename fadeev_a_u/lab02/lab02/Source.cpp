#include <opencv2/opencv.hpp>
#include <array>
using namespace cv;
using namespace std;

int main() {
    Mat img = imread("pic.png");
    imwrite("pic_good.jpeg", img, { IMWRITE_JPEG_QUALITY, 95 });
    imwrite("pic_bad.jpeg", img, { IMWRITE_JPEG_QUALITY, 65 });
    Mat img_good = imread("pic_good.jpeg");
    Mat img_bad = imread("pic_bad.jpeg");


    int cols = img.cols;
    int rows = img.rows;
    Mat result(rows * 3, cols * 4, CV_8UC3);
    img.copyTo(result(Rect2d(0, 0, rows, cols)));
    img_good.copyTo(result(Rect2d(0, rows, rows, cols)));
    img_bad.copyTo(result(Rect2d(0, 2*rows, rows, cols)));

    array<Mat, 3> ar;
    split(img, ar);



    for (int i = 0; i < 3; ++i) {
        Mat tmp;
        merge(array<Mat, 3>({ ar[i], ar[i], ar[i] }), tmp);
        tmp.copyTo(result(Rect2d((i+1) * cols, 0, rows, cols)));
    }

    array<Mat, 3> for_splitting;

    split(img_good, for_splitting);
    for (int i = 0; i < 3; ++i) {
        Mat tmp;
        absdiff(for_splitting[i], ar[i], tmp);
        merge(array<Mat, 3>({ tmp, tmp, tmp }), tmp);
        tmp.copyTo(result(Rect2d((i + 1) * cols, rows, rows, cols)));
    }

    split(img_bad, for_splitting);
    for (int i = 0; i < 3; ++i) {
        Mat tmp;
        absdiff(for_splitting[i], ar[i], tmp);
        merge(array<Mat, 3>({ tmp, tmp, tmp }), tmp);
        tmp.copyTo(result(Rect2d((i + 1) * cols, 2*rows, rows, cols)));
    }

    imshow("qwer", result);
    waitKey(0);
}