cmake_minimum_required(VERSION 3.15)
project(OpenCVExample)

set(CMAKE_CXX_STANDARD 17)
set(OpenCV_DIR C:/MULTIMEDIA/StudyPROGRAMMING/opencv/build)

find_package(OpenCV REQUIRED)

include_directories($(OpenCV_INCLUDE_DIRS))

add_executable(OpenCVExample T_OpenCVProj.cpp)

target_link_libraries(OpenCVExample ${OpenCV_LIBS})