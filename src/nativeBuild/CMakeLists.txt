cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_TOP_SOURCE_DIR}/.vendor/cmake/Modules")

project(frcUserProgram_NATIVE)

find_package(photonlib REQUIRED)
find_package(WPILib REQUIRED)
find_package(opencv REQUIRED)

# Detects the platform to build the native target for
if(WIN32)
  set(PLATFORM "windowsx86-64")
elseif(APPLE)
  set(PLATFORM "osxuniversal")
elseif(UNIX)
  set(PLATFORM "linuxx86-64")
endif()

# Robot host native target
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "${CMAKE_TOP_SOURCE_DIR}/src/main/*.cpp")
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCES})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    WPILib::${PLATFORM}::wpilibc-cpp
    WPILib::${PLATFORM}::hal-cpp
    WPILib::${PLATFORM}::cscore-cpp
    WPILib::${PLATFORM}::cameraserver-cpp
    WPILib::${PLATFORM}::wpiutil-cpp
    WPILib::${PLATFORM}::wpimath-cpp
    WPILib::${PLATFORM}::apriltag-cpp
    opencv::${PLATFORM}::opencv-cpp::opencv_imgcodecs
    opencv::${PLATFORM}::opencv-cpp::opencv_imgproc
    opencv::${PLATFORM}::opencv-cpp::opencv_core
    opencv::${PLATFORM}::opencv-cpp::opencv_videoio
    opencv::${PLATFORM}::opencv-cpp::opencv_ml
    opencv::${PLATFORM}::opencv-cpp::opencv_stitching
    opencv::${PLATFORM}::opencv-cpp::opencv_features2d
    opencv::${PLATFORM}::opencv-cpp::opencv_flann
    opencv::${PLATFORM}::opencv-cpp::opencv_highgui
    opencv::${PLATFORM}::opencv-cpp::opencv_video
    opencv::${PLATFORM}::opencv-cpp::opencv_photo
    opencv::${PLATFORM}::opencv-cpp::opencv_gapi
    opencv::${PLATFORM}::opencv-cpp::opencv_calib3d
    opencv::${PLATFORM}::opencv-cpp::opencv_objdetect
    opencv::${PLATFORM}::opencv-cpp::opencv_aruco
    photonlib::${PLATFORM}::PhotonLib-cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_TOP_SOURCE_DIR}/src/main/include")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${photonlib_INCLUDE_DIR} ${WPILib_INCLUDE_DIR})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
