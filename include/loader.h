/**
 * @brief 加载数据集
 * @author Bruce Hou
 * @update
 * @email ecstayalive@163.com
 */
#ifndef DIC_LOADER_H_
#define DIC_LOADER_H_

#include "types.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

/**
 * @brief 加载高速摄像机拍摄的图片
 */
class Loader {
private:
    /// 数据集存放路径
    const std::string PATH;

    /// 路径下的文件信息
    FileInfo fileinfo;

public:
    Loader();

    ~Loader();

    /**
     * @brief 唯一调用接口
     * @return 数据集
     */
    DataSet run();

private:
    /**
     * @brief 获取某一路径下的文件信息
     * @param path 路径
     * @return 是否获得信息成功
     */
    bool getFileInfo(const std::string &path);
};

# endif // DIC_LOADER_H_