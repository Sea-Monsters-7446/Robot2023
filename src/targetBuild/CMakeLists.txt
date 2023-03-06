cmake_minimum_required(VERSION 3.5)

project(frcUserProgram_TARGET)

include(${CMAKE_TOP_SOURCE_DIR}/.toolchain/roborio-academic/toolchain-config.cmake)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_TOP_SOURCE_DIR}/.vendor/cmake/Modules")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)

find_package(photonlib REQUIRED)
find_package(WPILib REQUIRED)
find_package(opencv REQUIRED)

# Robot host native target
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "${CMAKE_TOP_SOURCE_DIR}/src/main/*.cpp")
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCES})
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    opencv::linuxathena::opencv-cpp::opencv_imgcodecs
    opencv::linuxathena::opencv-cpp::opencv_imgproc
    opencv::linuxathena::opencv-cpp::opencv_core
    opencv::linuxathena::opencv-cpp::opencv_videoio
    opencv::linuxathena::opencv-cpp::opencv_ml
    opencv::linuxathena::opencv-cpp::opencv_stitching
    opencv::linuxathena::opencv-cpp::opencv_features2d
    opencv::linuxathena::opencv-cpp::opencv_flann
    opencv::linuxathena::opencv-cpp::opencv_highgui
    opencv::linuxathena::opencv-cpp::opencv_video
    opencv::linuxathena::opencv-cpp::opencv_photo
    opencv::linuxathena::opencv-cpp::opencv_gapi
    opencv::linuxathena::opencv-cpp::opencv_calib3d
    opencv::linuxathena::opencv-cpp::opencv_objdetect
    opencv::linuxathena::opencv-cpp::opencv_aruco
    WPILib::linuxathena::apriltag-cpp
    WPILib::linuxathena::hal-cpp
    WPILib::linuxathena::wpilibc-cpp
    WPILib::linuxathena::cscore-cpp
    WPILib::linuxathena::cameraserver-cpp
    WPILib::linuxathena::wpiutil-cpp
    WPILib::linuxathena::wpimath-cpp
    WPILib::linuxathena::runtime::embcanshim
    WPILib::linuxathena::runtime::fpgalvshim
    WPILib::linuxathena::netcomm
    WPILib::linuxathena::visa
    WPILib::linuxathena::chipobject
    photonlib::linuxathena::PhotonLib-cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_TOP_SOURCE_DIR}/src/main/include")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${photonlib_INCLUDE_DIR} ${WPILib_INCLUDE_DIR})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
