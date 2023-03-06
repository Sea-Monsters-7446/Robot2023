cmake_minimum_required(VERSION 3.5)
include(${CMAKE_SOURCE_DIR}/cmake/wpitools.cmake)
include(ExternalProject)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/.vendor/cmake/Modules")
list(APPEND CMAKE_ARGS "-DCMAKE_TOP_SOURCE_DIR=${CMAKE_SOURCE_DIR}")

project("SeaMonsters"
  LANGUAGES CXX
  DESCRIPTION "The code for the 2023 competition"
  HOMEPAGE_URL "https://github.com/FRC7446/Robot2023")

set(TEAM_NUMBER 7446)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(SKIP_VENDOR_CHECK "Skips the downloading/checking of vendor and custom dependancies" OFF)
option(SKIP_TOOLCHAIN_CHECK "Skips the downloading/checking of the cross compilation toolchain." OFF)

if(SKIP_VENDOR_CHECK)
  message(STATUS "Skipping vendor dependancy downloads/checks")
else()
  ensure_vendors_installed(PATHS "${CMAKE_SOURCE_DIR}/deps")
endif()

if(SKIP_TOOLCHAIN_CHECK)
  message(STATUS "Skipping toolchain download/check")
else()
  ensure_toolchain_installed()
endif()

externalproject_add(frcUserProgram_NATIVE
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/nativeBuild"
  CMAKE_ARGS ${CMAKE_ARGS}
  INSTALL_COMMAND cmake -E echo "No install step avaliable."
  BINARY_DIR "${CMAKE_BINARY_DIR}/frcUserProgram_NATIVE"
  TMP_DIR "${CMAKE_BINARY_DIR}/frcUserProgram_NATIVE/tmp"
  STAMP_DIR "${CMAKE_BINARY_DIR}/frcUserProgram_NATIVE/stamp"

)

externalproject_add(frcUserProgram_TARGET
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/targetBuild"
  CMAKE_ARGS ${CMAKE_ARGS}
  INSTALL_COMMAND cmake -E echo "No install step avaliable."
  BINARY_DIR "${CMAKE_BINARY_DIR}/frcUserProgram_TARGET"
  TMP_DIR "${CMAKE_BINARY_DIR}/frcUserProgram_TARGET/tmp"
  STAMP_DIR "${CMAKE_BINARY_DIR}/frcUserProgram_TARGET/stamp"
)

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

