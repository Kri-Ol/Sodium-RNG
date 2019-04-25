cmake_minimum_required(VERSION 3.14.0)
project(sodium VERSION 0.2.0)
project(sodium CXX)

include(CTest)
enable_testing()

add_executable(sodium main.cpp)
target_compile_features(sodium PUBLIC cxx_std_17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
