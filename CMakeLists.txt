cmake_minimum_required(VERSION 3.2)
project(NeuralNetworkCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(NeuralNetworkCPP ${SOURCE_FILES})


SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "E:/Boost")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "E:/Boost/libs")
FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()