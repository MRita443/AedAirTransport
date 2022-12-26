cmake_minimum_required(VERSION 3.24)
project(AirTransport)

set(CMAKE_CXX_STANDARD 17)

add_executable(AirTransport main.cpp airline.cpp airline.h airport.cpp airport.h graph.cpp graph.h menu.cpp menu.h position.cpp position.h)
