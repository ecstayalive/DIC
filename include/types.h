/**
 * @brief
 * @author Bruce Hou
 * @update
 * @email ecstayalive@163.com
 */

#ifndef DIC_TYPES_H_
#define DIC_TYPES_H_

#include <vector>
#include <opencv2/opencv.hpp>

/**
 * @brief 文件信息结构体
 * @details 给定相应路径下的所有文件的信息
 */
typedef struct FileInfo {
    std::vector<std::string> filename; ///< 文件名称队列
    int filenum = 0; ///< 该路径下的所有文件个数
} FileInfo;


/**
 * @brief 数据集结构体
 * @details 在数据集较小的时候加载所有数据集，并提供
   一些数据集的信息
 */
typedef struct DataSet {
    /// 数据集中的图片队列
    std::vector<cv::Mat> image;
    /// 数据集中的图片个数
    int sum_number = 0;

} DataSet;
#endif // DIC_TYPES_H_