#include "base.h"
#include "loader.h"
#include "types.h"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // 结构体声明
    DataSet dataset;

    // 类实例化
    Loader loader;

    dataset = loader.run();

    for (int i = 0; i < dataset.sum_number; i++) {
        imshow("img", dataset.image[i]);
        waitKey(1000);
    }
    return 0;
}

