
file(GLOB_RECURSE SERVER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp)
file(GLOB_RECURSE COMMON_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp)
file(GLOB_RECURSE CLIENT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp)

message(${SERVER_SRC_FILES})

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
