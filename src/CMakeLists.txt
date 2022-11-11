set(SERVER_SRC_FILES
#server_src/server.h
#server_src/server.cpp
	server/server_main.cpp
)

add_executable(server ${SERVER_SRC_FILES})

target_include_directories(server PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../inc)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../lib)

#target_link_libraries(server PUBLIC libbox2d.a)

# set(CLIENT_SRC_FILES
# 	client_src/client.h
# 	client_src/client.cpp
# 	client_src/client_main.cpp
# )
#[[
set(CLIENT_SRC_FILES
		client/*.cpp
		#client/ClientRocketLeague.cpp
		)]]
file(GLOB CLIENT_SRC_FILES client/*.cpp)
add_executable(client ${CLIENT_SRC_FILES})

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)

add_subdirectory(../lib/libSDL2pp ../build)

file(COPY client/assets DESTINATION ${CMAKE_BINARY_DIR}/src)

# Agrego la carpeta con los headers autogenerados a los includes
include_directories(${PROJECT_SOURCE_DIR}../lib)
include_directories(${SDL2PP_INCLUDE_DIRS})

target_link_libraries(client ${SDL2PP_LIBRARIES})
