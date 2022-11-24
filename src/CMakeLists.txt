
file(GLOB_RECURSE SERVER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/server/*.h)
file(GLOB_RECURSE COMMON_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/common/*.h)
file(GLOB_RECURSE CLIENT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp)


# --------- Server build ---------

add_executable(rl_server ${SERVER_SRC_FILES} ${COMMON_SRC_FILES})

target_include_directories(rl_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rl_server PUBLIC box2d yaml-cpp)

# copy config file to build directory
file(COPY ${CMAKE_CURRENT_LIST_DIR}/../.config.yml DESTINATION ${CMAKE_BINARY_DIR}/src)

target_compile_options(rl_server PUBLIC
	-Werror
	-Wall
	-O0
	-g
)

# --------- Client build ---------

add_executable(rocket_league ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES} )

target_include_directories(rocket_league PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# enabling image and font handling
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)

add_subdirectory(../lib/libSDL2pp ../build)

# copy resources to build directory
file(COPY client/assets DESTINATION ${CMAKE_BINARY_DIR}/src)

# adding SDL2pp libary
include_directories(${SDL2PP_INCLUDE_DIRS})
target_link_libraries(rocket_league PUBLIC ${SDL2PP_LIBRARIES})

target_compile_options(rocket_league PUBLIC
	-Werror
	-Wall
	-O0
	-g
)