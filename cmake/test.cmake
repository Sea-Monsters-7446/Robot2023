# Include the nlohmann/json library
include(FetchContent)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.4
)
FetchContent_MakeAvailable(json)

# Define the function to download and extract vendor libraries
function(ensure_vendors_installed)
  # Create the .vendor directory if it doesn't exist
  file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/.vendor)
  
  # Loop through each JSON file in the vendordeps directory
  file(GLOB JSON_FILES "${CMAKE_SOURCE_DIR}/vendordeps/*.json")
  foreach(JSON_FILE ${JSON_FILES})
    # Read the JSON data
    file(READ ${JSON_FILE} JSON_DATA)
    # Parse the JSON data using nlohmann/json
    json_parse(JSON "${JSON_DATA}")
    # Extract the relevant data from the parsed JSON
    set(mavenUrls "${JSON}.mavenUrls")
    set(binaryPlatforms "${JSON}.binaryPlatforms")
    set(groupID "${JSON}.groupID")
    set(artifactID "${JSON}.artifactID")
    set(version "${JSON}.version")
    # Download and extract the libraries for each URL in mavenUrls
    foreach(MAVEN_URL ${mavenUrls})
      message(STATUS "Downloading ${groupID}:${artifactID}:${version} from ${MAVEN_URL}")
      foreach(BINARY_PLATFORM ${binaryPlatforms})
        # Check whether the headers and library for the binary platform exist
        set(HEADER_URL "${MAVEN_URL}/${groupID}/${artifactID}/${version}/${artifactID}-${version}-${BINARY_PLATFORM}.h")
        set(LIBRARY_URL "${MAVEN_URL}/${groupID}/${artifactID}/${version}/${artifactID}-${version}-${BINARY_PLATFORM}.a")
        set(HEADER_FILE "${CMAKE_SOURCE_DIR}/.vendor/${groupID}/${artifactID}/${version}/${BINARY_PLATFORM}/${artifactID}.h")
        set(LIBRARY_FILE "${CMAKE_SOURCE_DIR}/.vendor/${groupID}/${artifactID}/${version}/${BINARY_PLATFORM}/${artifactID}.a")
        if(NOT EXISTS "${HEADER_FILE}" OR NOT EXISTS "${LIBRARY_FILE}")
          message(STATUS "Downloading ${artifactID} ${BINARY_PLATFORM} library and header files from ${MAVEN_URL}")
          file(DOWNLOAD ${HEADER_URL} ${HEADER_FILE})
          file(DOWNLOAD ${LIBRARY_URL} ${LIBRARY_FILE})
        endif()
      endforeach()
      message(STATUS "Downloaded and extracted ${groupID}:${artifactID}:${version}")
    endforeach()
  endforeach()
endfunction()