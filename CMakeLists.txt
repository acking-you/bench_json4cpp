cmake_minimum_required(VERSION 3.14)
project(bench_json4cpp VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
include_directories(./json/include/)
include_directories(./jsoncpp/include)
include_directories(./rapidjson/include)
include_directories(./sonic-cpp/include)

add_subdirectory(jsoncpp)

add_subdirectory(benchmark)


