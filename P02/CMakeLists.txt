cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)

project(Praktikum2)
add_executable(Praktikum2 ikomponente.h ikomponente.cpp komponente.h komponente.cpp bohrung.h bohrung.cpp fraesung.h fraesung.cpp delist.h delist.cpp ikomponente.h ikomponente.cpp ikomponente.cpp iterator.h iterator.cpp main.cpp ikomponentenelement.h werkstueck.h werkstueck.cpp)


#add_subdirectory(googletest)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
#target_link_libraries(Praktikum2GoogleTest gtest gtest_main)
