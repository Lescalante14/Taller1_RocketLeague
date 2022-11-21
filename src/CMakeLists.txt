set(SERVER_SRC_FILES
#server_src/server.h
#server_src/server.cpp
	server/server_main.cpp
)

add_executable(server ${SERVER_SRC_FILES})

target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/server)
target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/common)
target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/client)
target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/../inc)
target_include_directories(server ${CMAKE_CURRENT_LIST_DIR}/../lib)

target_link_libraries(server PUBLIC libbox2d.a)
target_link_libraries(server PUBLIC libyaml-cpp.a)

# set(CLIENT_SRC_FILES
# 	client_src/client.h
# 	client_src/client.cpp
# 	client_src/client_main.cpp
# )

# add_executable(client ${CLIENT_SRC_FILES})

# target_include_directories(client ${CMAKE_CURRENT_LIST_DIR}/../inc)
# target_include_directories(client ${CMAKE_CURRENT_LIST_DIR}/../lib)

# target_link_libraries(client PUBLIC lib2sdl.a)
