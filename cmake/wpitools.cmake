# Pull vendor libraries target and function yayyyyyy help me pls help me i need help
function(ensure_vendors_installed)
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/.vendor")
  file(GLOB_RECURSE vendor_library_jsons "${CMAKE_SOURCE_DIR}/vendordeps/*.json")
  foreach(CUR_FILE IN LISTS vendor_library_jsons)
    # reads current json into string
    file(READ ${CUR_FILE} CUR_JSON)

    string(JSON MAVEN_URLS ERROR_VARIABLE ERR GET ${CUR_JSON} "mavenUrls")

    # fudging, logic to iterate on the urls, if they exist, i guess
    if(NOT ${MAVEN_URLS} STREQUAL "mavenUrls-NOTFOUND")
      # grabs original length of the maven urls array i guess
      string(JSON _SIZE_MAVEN_URLS LENGTH ${MAVEN_URLS})

      # will not execute if there are no maven urls
      if(${_SIZE_MAVEN_URLS} GREATER 0)
        math(EXPR SIZE_MAVEN_URLS "${_SIZE_MAVEN_URLS} - 1")
        string(JSON CPP_DEPS GET ${CUR_JSON} "cppDependencies" 0)

        string(JSON GROUP_ID GET ${CPP_DEPS} "groupId")
        string(JSON ARTIFACT_ID GET ${CPP_DEPS} "artifactId")
        string(JSON DEP_VERSION GET ${CPP_DEPS} "version")
        string(JSON LIB_NAME GET ${CPP_DEPS} "libName")
        string(JSON HEADER_CLASSIFIER GET ${CPP_DEPS} "headerClassifier")
        string(JSON IS_SHARED GET ${CPP_DEPS} "sharedLibrary")
        string(JSON SKIP_INVALID_PLATFORMS GET ${CPP_DEPS} "skipInvalidPlatforms")
        string(JSON BINARY_PLATFORMS GET ${CPP_DEPS} "binaryPlatforms")
        string(JSON _BINARY_PLATFORMS_SIZE LENGTH ${BINARY_PLATFORMS})
        math(EXPR BINARY_PLATFORMS_SIZE "${_BINARY_PLATFORMS_SIZE} - 1")
        string(REPLACE "." "/" SPECIFIER ${GROUP_ID})

        file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/.vendor/${SPECIFIER}")
        file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/.vendor/${SPECIFIER}/lib")
        file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/.vendor/${SPECIFIER}/include")

        foreach(I RANGE ${SIZE_MAVEN_URLS})
          string(JSON URL GET ${MAVEN_URLS} ${I})

          set(HEADER_URL "")
          string(APPEND HEADER_URL ${URL} "/" ${SPECIFIER} "/" ${ARTIFACT_ID} "/" ${DEP_VERSION} "/" ${ARTIFACT_ID} "-" ${DEP_VERSION} "-" ${HEADER_CLASSIFIER} ".zip")
          message(STATUS "Downloading ${HEADER_URL}")
          file(DOWNLOAD ${HEADER_URL} SHOW_PROGRESS STATUS status)
          
          message(STATUS ${status})

          list(LENGTH ${status} len)

          if(${status} EQUAL 0)
            file(DOWNLOAD ${HEADER_URL} "${ARTIFACT_ID}-${DEP_VERSION}-${HEADER_CLASSIFIER}.zip" SHOW_PROGRESS)
          endif()
          foreach(_I RANGE ${BINARY_PLATFORMS_SIZE})
            set(LIB_URL "")

            string(JSON CUR_BINARY_PLATFORM GET ${BINARY_PLATFORMS} ${_I})
            string(APPEND LIB_URL ${URL} "/" ${SPECIFIER} "/" ${ARTIFACT_ID} "/" ${DEP_VERSION} "/" ${ARTIFACT_ID} "-" ${DEP_VERSION} "-" ${CUR_BINARY_PLATFORM} ".zip")
            
            message(STATUS ${LIB_URL})
          endforeach(_I RANGE ${_BINARY_PLATFORMS_SIZE})
        endforeach(I RANGE ${SIZE_MAVEN_URLS})
      endif()
    endif()
  endforeach(CUR_FILE IN LISTS vendor_library_jsons)
endfunction(ensure_vendors_installed)