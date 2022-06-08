cmake_minimum_required(VERSION 3.0.0)
project(ObjectSerialization VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

set(MOD_LIST tinyxml2)

include_directories(./include/)

foreach(modName IN LISTS MOD_LIST)
    add_library(${modName} STATIC ./src/${modName}.cpp)
endforeach()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
add_executable(test.out ./src/test.cpp)

foreach(modName IN LISTS MOD_LIST)
    target_link_libraries(test.out ${modName})
endforeach()