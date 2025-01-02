include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
        GIT_SHALLOW TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        nanobench
        GIT_REPOSITORY https://github.com/martinus/nanobench.git
        GIT_TAG v4.1.0
        GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nanobench)

FetchContent_Declare(
        ejson4cpp
        GIT_REPOSITORY https://github.com/acking-you/ejson4cpp.git
        GIT_TAG origin/master
        GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(ejson4cpp)


file(GLOB BENCH_FILES
        "${PROJECT_SOURCE_DIR}/benchmark/*.h"
        "${PROJECT_SOURCE_DIR}/benchmark/*.cc"
)

add_executable(json_bench ${BENCH_FILES})
target_link_libraries(json_bench PRIVATE gtest_main ejson jsoncpp_lib nanobench)
add_test(NAME json_bench COMMAND unittest)