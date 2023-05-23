#set minimun cmake version for build 
cmake_minimum_required(VERSION 3.5.0)
project(Parser VERSION 0.0.1)

#set miniimum c++ standart 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#include all files for build project
set(RESOURCE_FILES
    main.cpp 
)

#set outputs directorry
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

##build
if(APPLE)
add_executable(Parser+${VERSION} ${RESOURCE_FILES})
set_target_properties(Parser+${VERSION}  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(Parser+${VERSION}  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) #include resource files


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug) 
message(Parser+${VERSION} ${CMAKE_BINARY_DIR}/debug)
endif()
###