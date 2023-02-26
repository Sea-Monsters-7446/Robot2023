cmake_minimum_required(VERSION 3.2)
include(${CMAKE_SOURCE_DIR}/cmake/wpitools.cmake)
#include(${CMAKE_TOOLCHAIN_FILE})

ensure_vendors_installed()
project("SeaMonsters" 
  LANGUAGES CXX
  DESCRIPTION "The code for the 2023 competition"
  HOMEPAGE_URL "https://github.com/FRC7446/Robot2023")

set(TEAM_NUMBER 7446)

# Robot target
# For quick list of files run
# find src -iname "*.cpp"
# in project root
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "${CMAKE_SOURCE_DIR}/src/main/*.cpp")
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src/main/include")

# Example: adding CTRE library
# Make sure this goes before WPILib
# find_package(CTRE)
# include_directories(${CTRE_INCLUDE_DIR})
# target_link_libraries(${PROJECT_NAME} ${CTRE_LIBRARIES})

#find_package(WPILib)
#include_directories(${WPILIB_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} ${WPILIB_LIBRARIES})
#include_directories( "src" )

# Test target
include(ExternalProject)
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

