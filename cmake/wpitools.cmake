# Pull vendor libraries target and function yayyyyyy help me pls help me i need help
function(ensure_vendors_installed)
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/.vendor")
  file(GLOB_RECURSE vendor_library_jsons "${CMAKE_SOURCE_DIR}/vendordeps/*.json")
  foreach(CUR_FILE IN LISTS vendor_library_jsons)
    # reads current json into string
    file(READ ${CUR_FILE} CUR_JSON)

    string(JSON MAVEN_URLS ERROR_VARIABLE ERR GET ${CUR_JSON} "mavenUrls")
    string(JSON LIB_FILE_NAME GET ${CUR_JSON} "name")

    # fudging, logic to iterate on the urls, if they exist, i guess
    if(NOT ${MAVEN_URLS} STREQUAL "mavenUrls-NOTFOUND")
      # grabs original length of the maven urls array i guess
      string(JSON _SIZE_MAVEN_URLS LENGTH ${MAVEN_URLS})

      # will not execute if there are no maven urls
      if(${_SIZE_MAVEN_URLS} GREATER 0)
        # grabs cpp deps part of json
        string(JSON _CPP_DEPS GET ${CUR_JSON} "cppDependencies")
        string(JSON __CPP_DEPS_SIZE LENGTH ${_CPP_DEPS})
        math(EXPR _CPP_DEPS_SIZE "${__CPP_DEPS_SIZE} - 1")

        string(REPLACE " " "_" CONFIG_NAME ${LIB_FILE_NAME})
        string(REPLACE "(" "" CONFIG_NAME ${CONFIG_NAME})
        string(REPLACE ")" "" CONFIG_NAME ${CONFIG_NAME})

        # library where the object and header files are stored
        set(VENDOR_DIRECTORY "${CMAKE_SOURCE_DIR}/.vendor/${CONFIG_NAME}")

        # set folders
        file(MAKE_DIRECTORY ${VENDOR_DIRECTORY})
        file(MAKE_DIRECTORY "${VENDOR_DIRECTORY}/lib")
        file(MAKE_DIRECTORY "${VENDOR_DIRECTORY}/include")

        # lloops on each of da cpp deps
        foreach(IT RANGE ${_CPP_DEPS_SIZE})
          string(JSON CPP_DEPS GET ${_CPP_DEPS} ${IT})
          math(EXPR SIZE_MAVEN_URLS "${_SIZE_MAVEN_URLS} - 1")
          
          # extracts and gives variables to everything from cpp deps part of json
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

          # configure da file fur cmake so we can include it in our project

          set(PACKAGE_INCLUDE_DIR "${VENDOR_DIRECTORY}/include")
          set(PACKAGE_BASE_LIBRARY_DIR "${VENDOR_DIRECTORY}/lib")
          set(PACKAGE_VERSION ${DEP_VERSION})

          # loop over maven url
          foreach(I RANGE ${SIZE_MAVEN_URLS})
            set(URL "")
            set(HEADER_URL "")
            set(STATUS_LIST "")

            string(JSON URL GET ${MAVEN_URLS} ${I})

            string(LENGTH ${URL} _URL_LENGTH)
            math(EXPR URL_LENGTH "${_URL_LENGTH} - 1")

            string(SUBSTRING ${URL} ${URL_LENGTH} 1 URL_LAST)

            if(${URL_LAST} STREQUAL "/")
              string(SUBSTRING ${URL} 0 ${URL_LENGTH} URL)
            endif()

            # do bazinga stuff to bam bam boom get the possible location to download the headers
            string(APPEND HEADER_URL ${URL} "/" ${SPECIFIER} "/" ${ARTIFACT_ID} "/" ${DEP_VERSION} "/" ${ARTIFACT_ID} "-" ${DEP_VERSION} "-" ${HEADER_CLASSIFIER} ".zip")
            message(STATUS "Checking avaliability for: ${HEADER_URL}")
            file(DOWNLOAD ${HEADER_URL} STATUS STATUS_LIST)

            list(GET STATUS_LIST 0 STATUS)
            list(GET STATUS_LIST 1 STATUS_READABLE)

            # downloads the headers if the link is valid
            # also checks tu c if the file is update
            if(${STATUS} EQUAL 0)
              message(STATUS "Checking/Downloading: ${HEADER_URL}")
              set(FILE "${VENDOR_DIRECTORY}/${ARTIFACT_ID}-${DEP_VERSION}-${HEADER_CLASSIFIER}.zip")

              if(NOT EXISTS "${FILE}.md5")
                file(DOWNLOAD ${HEADER_URL} ${FILE} SHOW_PROGRESS)
                message(STATUS "Downloaded to: ${FILE}")
                message(STATUS "Generating MD5 Hash of file...")
                file(MD5 ${FILE} FILE_CHECKSUM)
                file(WRITE "${FILE}.md5" ${FILE_CHECKSUM})
                message(STATUS "Extracting ${FILE}")
                # do dah guud header extraction lmao
                file(ARCHIVE_EXTRACT INPUT ${FILE} DESTINATION "${VENDOR_DIRECTORY}/include" VERBOSE)
              else()
                file(READ "${FILE}.md5" FILE_CHECKSUM)
                file(DOWNLOAD ${HEADER_URL} ${FILE} SHOW_PROGRESS EXPECTED_MD5 ${FILE_CHECKSUM} STATUS DOWNLOAD_STATUS)
                list(GET DOWNLOAD_STATUS 0 STATUS)

                if(NOT ${STATUS} EQUAL 0)
                  message(STATUS "File has been updated, regenerating MD5 Hash...")
                  file(MD5 ${FILE} FILE_CHECKSUM)
                  file(WRITE "${FILE}.md5" ${FILE_CHECKSUM})
                  message(STATUS "Extracting newer ${FILE}")
                  # do dah guud header extraction lmao
                  file(ARCHIVE_EXTRACT INPUT ${FILE} DESTINATION "${VENDOR_DIRECTORY}/include" VERBOSE)
                else()
                  message(STATUS "File up to date, skipping download")
                endif()

              endif()
            else()
              message(WARNING "Error checking for `${HEADER_URL}`: Error code: ${STATUS}: ${STATUS_READABLE}")
            endif()

            # loops over the binary platforms like the little, nvm
            foreach(_I RANGE ${BINARY_PLATFORMS_SIZE})

              set(LIB_URL "")
              set(STATUS_LIST "")

              set(LIBRARY "${ARTIFACT_ID}-${CUR_BINARY_PLATFORM}")

              string(JSON CUR_BINARY_PLATFORM GET ${BINARY_PLATFORMS} ${_I})

              # generates the full url to download a possible lib file
              string(APPEND LIB_URL ${URL} "/" ${SPECIFIER} "/" ${ARTIFACT_ID} "/" ${DEP_VERSION} "/" ${ARTIFACT_ID} "-" ${DEP_VERSION} "-" ${CUR_BINARY_PLATFORM} ".zip")
              
              message(STATUS "Checking avaliability for: ${LIB_URL}")

              file(DOWNLOAD ${LIB_URL} STATUS STATUS_LIST)
              list(GET STATUS_LIST 0 STATUS)
              list(GET STATUS_LIST 1 STATUS_READABLE)
              
              if(${STATUS} EQUAL 0)
                set(FILE "")

                # downloabs da libs lul
                message(STATUS "Downloading/Checking: ${LIB_URL}")
                set(FILE "${VENDOR_DIRECTORY}/${ARTIFACT_ID}-${DEP_VERSION}-${CUR_BINARY_PLATFORM}.zip")
                
                if(NOT EXISTS "${FILE}.md5")
                  # executes if the hash file does not exist, so needs to download no matter what

                  file(DOWNLOAD ${LIB_URL} ${FILE} SHOW_PROGRESS)
                  message(STATUS "Downloaded to: ${FILE}")

                  message(STATUS "Extracting ${FILE}")
                  # do dah guud lib extraction lmao
                  file(ARCHIVE_EXTRACT INPUT ${FILE} DESTINATION "${VENDOR_DIRECTORY}/lib/${CUR_BINARY_PLATFORM}" VERBOSE)
                  # generat da guud md5 hasshh
                  message(STATUS "Generating MD5 Hash of file...")
                  file(MD5 ${FILE} FILE_CHECKSUM)
                  file(WRITE "${FILE}.md5" ${FILE_CHECKSUM})
                  
                else()
                  # executes if the has file exists
                  # cechks the hash against the download

                  file(READ "${FILE}.md5" FILE_CHECKSUM)
                  file(DOWNLOAD ${LIB_URL} ${FILE} SHOW_PROGRESS EXPECTED_MD5 ${FILE_CHECKSUM} STATUS DOWNLOAD_STATUS)
                  list(GET DOWNLOAD_STATUS 0 STATUS)

                  if(NOT ${STATUS} EQUAL 0)

                    # regen the hash if its been updated
                    message(STATUS "File has been updated, regenerating MD5 Hash...")
                    file(MD5 ${FILE} FILE_CHECKSUM)
                    file(WRITE "${FILE}.md5" ${FILE_CHECKSUM})

                    message(STATUS "Extracting newer ${FILE}")
                    # do dah guud lib extraction lmao
                    file(ARCHIVE_EXTRACT INPUT ${FILE} DESTINATION "${VENDOR_DIRECTORY}/lib/${CUR_BINARY_PLATFORM}" VERBOSE)
                  else()
                    message(STATUS "File up to date, skipping download")
                  endif()
                endif()
              else()
                message(WARNING "Error checking for `${LIB_URL}`: Error code: ${STATUS}: ${STATUS_READABLE}")
              endif()
            endforeach(_I RANGE ${_BINARY_PLATFORMS_SIZE})
          endforeach(I RANGE ${SIZE_MAVEN_URLS})
        endforeach(IT IN RANGE ${_CPP_DEPS_SIZE})
        # configures the file so that cmake can find it
        configure_file("${CMAKE_SOURCE_DIR}/cmake/FindPackage.cmake.in" "${CMAKE_SOURCE_DIR}/.vendor/cmake/Modules/Find${CONFIG_NAME}.cmake" @ONLY)
      endif()
    endif()
  endforeach(CUR_FILE IN LISTS vendor_library_jsons)
endfunction(ensure_vendors_installed)