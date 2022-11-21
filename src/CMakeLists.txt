
file(GLOB COMMON_SRC_FILES common/*.cpp)

file(GLOB SERVER_SRC_FILES server/*.cpp)

add_executable(server ${SERVER_SRC_FILES} ${COMMON_SRC_FILES})

target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/server)
target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/common)
target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/client)
target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/../inc)
target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/../lib)

<<<<<<< HEAD
target_link_libraries(server PUBLIC libbox2d.a)
target_link_libraries(server PUBLIC libyaml-cpp.a)
=======
target_link_libraries(server PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../lib/libbox2d.a)
>>>>>>> main

# set(CLIENT_SRC_FILES
# 	client_src/client.h
# 	client_src/client.cpp
# 	client_src/client_main.cpp
# )

# add_executable(client ${CLIENT_SRC_FILES})

# target_include_directories(client ${CMAKE_CURRENT_LIST_DIR}/../inc)
# target_include_directories(client ${CMAKE_CURRENT_LIST_DIR}/../lib)

# target_link_libraries(client PUBLIC lib2sdl.a)
