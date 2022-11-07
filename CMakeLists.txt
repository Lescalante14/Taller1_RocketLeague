cmake_minimum_required(VERSION 3.22)

project(rocket-league)

add_executable(server src/server/server_main.cpp)
add_executable(client src/client/client_main.cpp)
