
file(GLOB_RECURSE SERVER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp)
file(GLOB_RECURSE COMMON_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp)
file(GLOB_RECURSE CLIENT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp)


# --------- Server build ---------

add_executable(server ${SERVER_SRC_FILES} ${COMMON_SRC_FILES})

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(server PUBLIC box2d yaml-cpp)

# add_executable(client ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES})


# target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(server PUBLIC sdl2 yaml-cpp)

target_compile_options(server PUBLIC
	-Werror
	-Wall
	-O3
	-g
)

# --------- Client build ---------

add_executable(client ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES} )

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)

add_subdirectory(../lib/libSDL2pp ../build)

file(COPY client/assets DESTINATION ${CMAKE_BINARY_DIR}/src)

# Agrego la carpeta con los headers autogenerados a los includes
include_directories(${PROJECT_SOURCE_DIR}../lib)
include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src/client/presentation)

target_link_libraries(client PUBLIC ${SDL2PP_LIBRARIES})

target_compile_options(client PUBLIC
	-Werror
	-Wall
	-O3
	-g
)