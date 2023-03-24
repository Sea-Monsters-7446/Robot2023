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
option(RECONFIGURE_LIBRARIES "Reconfigure the Find<VendorLibrary>.cmake files" FALSE)

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

# Deploy target
externalproject_get_property(frcUserProgram_TARGET BINARY_DIR)
add_custom_target(deploy
    COMMAND sh -c "${CMAKE_CURRENT_SOURCE_DIR}/cmake/deploy ${TEAM_NUMBER} ${BINARY_DIR}/frcUserProgram_TARGET"
  DEPENDS frcUserProgram_TARGET)
set_target_properties(deploy PROPERTIES EXCLUDE_FROM_ALL TRUE)
