cmake_minimum_required(VERSION 3.16)

# 项目
project(DIC)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_NAME DIC)

# 设置第三方库
find_package(OpenCV REQUIRED)


# 指定头文件目录
include_directories(./include
        ${OpenCV_INCLUDE_DIRS}
        )

#
file(GLOB sourcefile "./src/*.cpp")

add_executable(${PROJECT_NAME}
        main.cpp
        ${sourcefile}
        )

# 添加动态连接库
target_link_libraries(${PROJECT_NAME}
        ${OpenCV_LIBRARIES}
        -pthread
        )