cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)

project(Praktikum1)
add_executable(Praktikum1 main.cpp komponente.h komponente.cpp bohrung.h bohrung.cpp fraesung.h fraesung.cpp komponentenList.h komponentenList.cpp)


add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
add_executable(Praktikum1GoogleTest p01TestMain.cpp komponente.h komponente.cpp bohrung.h bohrung.cpp fraesung.h fraesung.cpp komponentenList.h komponentenList.cpp)
target_link_libraries(Praktikum1GoogleTest gtest gtest_main)
