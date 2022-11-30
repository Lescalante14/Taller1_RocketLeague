cmake_minimum_required(VERSION 3.22)
project(rocket-league)

include_directories(${CMAKE_CURRENT_LIST_DIR}/inc)
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)

add_subdirectory(src)
