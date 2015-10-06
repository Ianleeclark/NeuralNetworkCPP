cmake_minimum_required(VERSION 2.8)
project(NeuralNetworkCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "D:/Boost")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "D:/Boost/libs")
FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()
set(SOURCE_FILES main.cpp)
add_executable(NeuralNetworkCPP ${SOURCE_FILES})

add_subdirectory("SMS")
add_subdirectory("unit_tests")


