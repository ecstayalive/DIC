#include "process.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Process::Process() {
    writer.open("../result/result.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 25, Size(1920, 1200));
}

Process::~Process() = default;

vector<vector<Point>> Process::run(const DataSet &dataset) {
    Mat image;
    vector<vector<Point>> result;
    for (int i = 0; i < dataset.sum_number; ++i) {
        image = dataset.image[i].clone();
//        cout << image.size() << endl;
//        imshow("image", image);
        vector<Point> targetPoint;
        vector<Rect> targetRect = getTarget(image);
        for (int i = 0; i < targetRect.size(); ++i) {
            targetPoint.emplace_back((targetRect[i].tl() + targetRect[i].br()) / 2);
            rectangle(image, targetRect[i], Scalar(0, 255, 0), 8, 8);
            circle(image, targetPoint[i], 5, Scalar(255, 0, 0), -1, 8);
        }
        imshow("image after process", image);
        writer << image;
        waitKey(100);
//        if (waitKey() > 0)
        result.emplace_back(targetPoint);
    }
    return result;
}

vector<Rect> Process::getTarget(Mat &InputImage) {
    Rect rect(920, 400, 100, 600);  ///< 矩形大小
    Mat normImage;  ///< 规范化图像
    Mat dstImage;  ///< 角点检测后的图像结果
    Mat thredImage;   ///< 最后的二值化图像
    Mat rgb_image;
    Mat image;

    // 截取
    rgb_image = InputImage(rect);
    cvtColor(rgb_image, image, COLOR_BGR2GRAY);
    dstImage = Mat::zeros(image.size(), CV_32FC1);
    // 角点检测
    cornerHarris(image, dstImage, 10, 3, 0.13, BORDER_DEFAULT);
    // 二值化
    threshold(dstImage, thredImage, 0.0001, 255, THRESH_BINARY);
    // 膨胀操作
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    dilate(thredImage, thredImage, structureElement, Point(-1, -1), 1);
    thredImage.convertTo(thredImage, CV_8UC1);
//    imshow("thredImage", thredImage);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    // 寻找轮廓
    findContours(thredImage, contours, hierarchy, 0, CHAIN_APPROX_SIMPLE, Point(0, 0));
//    // 绘制轮廓
//    for (int i = 0; i < contours.size(); i++) {
//        drawContours(rgb_image, contours, i, Scalar(0, 255, 0), -1, 8);
//    }
    Rect bounds[contours.size()];  ///< 轮廓外接矩形
    vector<Point> points;  ///< 角点坐标
    vector<Point> points1, points2;  ///< 两组角点坐标
    for (int i = 0; i < contours.size(); ++i) {
        bounds[i] = boundingRect(contours[i]);
        Point temp_point = (bounds[i].tl() + bounds[i].br()) / 2;
        points.emplace_back(temp_point + Point(920, 400));
//        rectangle(rgb_image, bounds[i], Scalar(0, 255, 0), 3, 8);
//        circle(rgb_image, temp_point, 2, Scalar(0, 0, 255), -1, 8);
    }
//    imshow("rgb_image", rgb_image);
    // 将点分类
    for (int i = 0; i < 4; ++i) {
        points1.emplace_back(points[i]);
        points2.emplace_back(points[i + 4]);
    }
    vector<Rect> result;
    result.emplace_back(boundingRect(points1));
    result.emplace_back(boundingRect(points2));
    return result;
}

Mat Process::getHistograph(const Mat &image) {
    /// 定义求直方图的通道数目
    int channels[] = {0};
    /// 定义直方图的在每一维上的大小，例如灰度图直方图的横坐标是图像的灰度值
    /// 如果直方图图像横坐标bin个数为x，纵坐标bin个数为y，则channels[]={1,2}其直方图应该为三维的，Z轴是每个bin上统计的数目
    const int histSize[] = {256};
    /// 每一维bin的变化范围
    float range[] = {0, 256};

    /// 所有bin的变化范围，个数跟channels应该跟channels一致
    const float *ranges[] = {range};

    /// 定义直方图，这里求的是直方图数据
    Mat hist;
    // opencv中计算直方图的函数，hist大小为256*1，每行存储的统计的该行对应的灰度值的个数
    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);

    // 找出直方图统计的个数的最大值，用来作为直方图纵坐标的高
    double maxValue = 0;
    // 找矩阵中最大最小值及对应索引的函数
    minMaxLoc(hist, 0, &maxValue, 0, 0);
    // 最大值取整
    int rows = cvRound(maxValue);
    // 定义直方图图像，直方图纵坐标的高作为行数，列数为256(灰度值的个数)
    // 因为是直方图的图像，所以以黑白两色为区分，白色为直方图的图像
    Mat histImage = Mat::zeros(rows, 256, CV_8UC1);

    // 直方图图像表示
    for (int i = 0; i < 256; i++) {
        // 取每个bin的数目
        int temp = (int) (hist.at<float>(i, 0));
        // 如果bin数目为0，则说明图像上没有该灰度值，则整列为黑色
        // 如果图像上有该灰度值，则将该列对应个数的像素设为白色
        if (temp) {
            // 由于图像坐标是以左上角为原点，所以要进行变换，使直方图图像以左下角为坐标原点
            histImage.col(i).rowRange(Range(rows - temp, rows)) = 255;
        }
    }
    // 由于直方图图像列高可能很高，因此进行图像对列要进行对应的缩减，使直方图图像更直观
    Mat resizeImage;
    resize(histImage, resizeImage, Size(512, 512));
    return resizeImage;
}


