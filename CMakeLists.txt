cmake_minimum_required(VERSION 3.5)
include(${CMAKE_SOURCE_DIR}/cmake/wpitools.cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/.vendor/cmake/Modules")
#include(${CMAKE_TOOLCHAIN_FILE})

project("SeaMonsters" 
  LANGUAGES CXX
  DESCRIPTION "The code for the 2023 competition"
  HOMEPAGE_URL "https://github.com/FRC7446/Robot2023")

set(TEAM_NUMBER 7446)

option(SKIP_VENDOR_CHECK SKIP_CHECK)

if(SKIP_CHECK EQUAL OFF)
  ensure_vendors_installed(PATHS "${CMAKE_SOURCE_DIR}/deps")
endif()

find_package(photonlib REQUIRED)
find_package(WPILib REQUIRED)

# Robot target
# For quick list of files run
# find src -iname "*.cpp"
# in project root
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "${CMAKE_SOURCE_DIR}/src/main/*.cpp")
add_executable("${PROJECT_NAME}_NATIVE")
target_sources("${PROJECT_NAME}_NATIVE" PRIVATE ${${PROJECT_NAME}_SOURCES})
target_include_directories("${PROJECT_NAME}_NATIVE" PRIVATE "${CMAKE_SOURCE_DIR}/src/main/include")
target_link_directories("${PROJECT_NAME}_NATIVE" PRIVATE "${WPILib_BASE_LIBRARY_DIR}/linuxx86-64/linux/x86-64/shared" "${photonlib_BASE_LIBRARY_DIR}/linuxx86-64/linux/x86_64/shared")
target_include_directories("${PROJECT_NAME}_NATIVE" SYSTEM PUBLIC ${photonlib_INCLUDE_DIR} ${WPILib_INCLUDE_DIR})

set_property(TARGET "${PROJECT_NAME}_NATIVE" PROPERTY CXX_STANDARD 20)

#include(ExternalProject)
#ExternalProject_Add(check
#  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/test
#  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/test/src
#  INSTALL_COMMAND ""
#  TEST_AFTER_INSTALL 1
#  TEST_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test/src/check-build/check)
#set_target_properties(check PROPERTIES EXCLUDE_FROM_ALL TRUE)

# Deploy target
#find_file(ROBOTCOMMAND ant/robotCommand PATHS "${CMAKE_SYSROOT}/usr/share/wpilib" "${CMAKE_SYSROOT}/wpilib")
#add_custom_target(deploy
#  COMMAND sh -c "${CMAKE_CURRENT_SOURCE_DIR}/deploy ${TEAM_NUMBER} $<TARGET_FILE:${PROJECT_NAME}> ${ROBOTCOMMAND}"
#  DEPENDS ${PROJECT_NAME})
#set_target_properties(deploy PROPERTIES EXCLUDE_FROM_ALL TRUE)

# Lint target
add_custom_target(lint
    COMMAND sh -c "cppcheck src --enable=information,warning,style -I src"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

