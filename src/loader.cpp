#include <dirent.h>
#include "loader.h"
#include "types.h"


using namespace std;
using namespace cv;

Loader::Loader() : PATH("../dataset/") {}

Loader::~Loader() {}

DataSet Loader::run() {
    DataSet dataset;
    // 文件信息
    if (getFileInfo(PATH)) {
        for (int i = 0; i < fileinfo.filenum; i++) {
            // 加载
            Mat img = imread(PATH + fileinfo.filename[i]);
            dataset.image.emplace_back(img);
            dataset.sum_number++;
        }
    }
    // 读取完成
    return dataset;
}

bool Loader::getFileInfo(const string &path) {
    fileinfo.filenum = 0;

    struct dirent **namelist;
    int sum_number;
    sum_number = scandir(path.c_str(), &namelist, 0, alphasort);
    // 判断路径是否存在
    if (sum_number < 0) {
        // 路径不存在，返回错误
        return false;
    }
    // 统计路径中的文件信息
    int index = 0;
    while (index < sum_number) {
        if (strcmp(namelist[index]->d_name, ".") != 0 && strcmp(namelist[index]->d_name, "..") != 0) {
            fileinfo.filenum++;
            fileinfo.filename.emplace_back(namelist[index]->d_name);
//            cout << namelist[index]->d_name << endl;
        }
        index++;
    }
    free(namelist);

    return true;
}