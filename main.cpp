#include "base.h"
#include "loader.h"
#include "process.h"
#include "types.h"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // 结构体声明
    DataSet dataset;  ///< 数据集
    vector<vector<Point>> targetPoint;   ///< 目标点
    // 类实例化
    Loader loader;
    Process process;
    // 获取数据集
    dataset = loader.run();
    // 获得图像处理结果
    targetPoint = process.run(dataset);

    return 0;
}

