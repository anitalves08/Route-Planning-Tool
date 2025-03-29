cmake_minimum_required(VERSION 3.30)
project(Route_Planning_Tool_v2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Route_Planning_Tool_v2 main.cpp
        DataLoader.cpp
        PathFinder.cpp
        DataLoader.h
        PathFinder.h
        Location.h
        Graph.h
        MutablePriorityQueue.h
)
