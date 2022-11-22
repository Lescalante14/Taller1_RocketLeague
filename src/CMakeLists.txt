
file(GLOB COMMON_SRC_FILES common/*.cpp)

# --------- Server build ---------
file(GLOB SERVER_SRC_FILES server/*.cpp)

add_executable(server ${SERVER_SRC_FILES} ${COMMON_SRC_FILES})

target_include_directories(server PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../inc)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../lib)

target_link_libraries(server PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../lib/libbox2d.a)

# --------- Client build ---------

file(GLOB CLIENT_SRC_FILES client/*.cpp client/presentation/*.cpp client/model/*.cpp client/helpers/*.cpp)
add_executable(client ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES} )

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)

add_subdirectory(../lib/libSDL2pp ../build)

file(COPY client/assets DESTINATION ${CMAKE_BINARY_DIR}/src)

# Agrego la carpeta con los headers autogenerados a los includes
include_directories(${PROJECT_SOURCE_DIR}../lib)
include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src/client/presentation)

target_link_libraries(client ${SDL2PP_LIBRARIES})
