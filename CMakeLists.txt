cmake_minimum_required(VERSION 3.0.0)
project(cpp_demo VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
include_directories(./yazi-json/json/)
include_directories(./json/single_include/)
include_directories(./jsoncpp/include)
add_subdirectory(jsoncpp)

add_executable(cpp_demo main.cpp ./yazi-json/json/Json.cpp  ./yazi-json/json/Parser.cpp my-json/JObject.cpp my-json/Parser.cpp)
target_link_libraries(cpp_demo jsoncpp_lib)


