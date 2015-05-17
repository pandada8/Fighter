cmake_minimum_required(VERSION 3.1)
project(Flight)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH "/usr/share/cmake-3.2/Modules/")
#set(CMAKE_BUILD_TYPE Release) #If you have problems check if you have SFML debug libraries or release libraries
set(CMAKE_C_FLAGS_DEBUG "-DFLYING")
find_package(SFML 2.3 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})
set(SOURCE_FILES main.cpp)
add_executable(Flight ${SOURCE_FILES})
target_link_libraries(Flight ${SFML_LIBRARIES})
