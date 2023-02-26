cmake_minimum_required(VERSION 3.2)
#include(${CMAKE_TOOLCHAIN_FILE})

# Pull vendor libraries target and function yayyyyyy help me pls help me i need help
function(ensure_vendor_installed)
  file(GLOB_RECURSE vendor_library_jsons "${CMAKE_SOURCE_DIR}/vendordeps/*.json")
  foreach(CUR_FILE IN LISTS vendor_library_jsons)
    # reads current json into string
    file(READ ${CUR_FILE} CUR_JSON)

    string(JSON MAVEN_URLS ERROR_VARIABLE ERR GET ${CUR_JSON} "mavenUrls")

    # fudging, logic to iterate on the urls, if they exist, i guess
    if(NOT ${MAVEN_URLS} STREQUAL "mavenUrls-NOTFOUND")
      string(JSON _SIZE LENGTH ${MAVEN_URLS})
      if(${_SIZE} GREATER 0)
        math(EXPR SIZE "${_SIZE} - 1")
        string(JSON CPP_DEPS GET ${CUR_JSON} "cppDependencies" 0)

        string(JSON GROUP_ID GET ${CPP_DEPS} "groupId")
        string(JSON ARTIFACT_ID GET ${CPP_DEPS} "artifactId")
        string(JSON DEP_VERSION GET ${CPP_DEPS} "version")
        string(JSON LIB_NAME GET ${CPP_DEPS} "libName")
        string(JSON HEADER_ClASSIFIER GET ${CPP_DEPS} "headerClassifier")
        string(JSON IS_SHARED GET ${CPP_DEPS} "sharedLibrary")
        string(JSON SKIP_INVALID_PLATFORMS GET ${CPP_DEPS} "skipInvalidPlatforms")
        string(JSON BINARY_PLATFORMS GET ${CPP_DEPS} "binaryPlatforms")
        string(JSON _BINARY_PLATFORMS_SIZE LENGTH ${BINARY_PLATFORMS})
        math(EXPR BINARY_PLATFORMS_SIZE "${_BINARY_PLATFORMS_SIZE} - 1")

        foreach(I RANGE ${SIZE})
          foreach(_I RANGE ${BINARY_PLATFORMS_SIZE})         
            string(JSON URL GET ${MAVEN_URLS} ${I})
            string(JSON CUR_BINARY_PLATFORM GET ${BINARY_PLATFORMS} ${_I})
            string(REPLACE "." "/" SPECIFIER ${GROUP_ID})
            string(APPEND URL "/" ${SPECIFIER} "/" ${ARTIFACT_ID} "/" ${DEP_VERSION} "/" ${ARTIFACT_ID} "-" ${DEP_VERSION} "-" ${CUR_BINARY_PLATFORM} ".zip")
            message(STATUS ${URL})
          endforeach(_I RANGE ${_BINARY_PLATFORMS_SIZE})
        endforeach(I RANGE ${SIZE})
      endif()
    endif()
  endforeach()
endfunction(ensure_vendor_installed)

ensure_vendor_installed()
project("SeaMonsters" 
  LANGUAGES CXX
  DESCRIPTION "The code for the 2023 competition"
  HOMEPAGE_URL "https://github.com/FRC7446/Robot2023")

set(TEAM_NUMBER 7446)

# Robot target
# For quick list of files run
# find src -iname "*.cpp"
# in project root
file(GLOB_RECURSE monsters2023_sources "${CMAKE_SOURCE_DIR}/src")
add_executable(${PROJECT_NAME} ${monsters2023_sources})
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

