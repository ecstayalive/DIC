/**
 * @brief
 * @author Bruce Hou
 * @update
 * @email ecstayalive@163.com
 */
#ifndef DIC_PROCESS_H
#define DIC_PROCESS_H

#include "types.h"
#include <vector>
#include <opencv2/opencv.hpp>

/**
 * @brief 对获取的数据集进行加工处理
 */
class Process {
private:
    cv::VideoWriter writer;
public:
    Process();

    ~Process();

    /**
     * @brief 函数调用接口
     */
    std::vector<std::vector<cv::Point>> run(const DataSet &dataset);

private:

    /**
     * @brief 根据输入的二值图像，得到目标点
     */
    std::vector<cv::Rect> getTarget(cv::Mat &InputImage);

    /**
     * @brief 获取图像的灰度直方图，仅在调试的时侯使用
     */
    cv::Mat getHistograph(const cv::Mat &image);

};

#endif // DIC_PROCESS_H