
file(GLOB_RECURSE SERVER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/server/*.h)
file(GLOB_RECURSE COMMON_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/common/*.h)
file(GLOB_RECURSE CLIENT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/client/*.h)

file(GLOB_RECURSE QT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/qt-menu/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/client/*.h)
file(GLOB_RECURSE QT_UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/qt-menu/*.ui)

add_subdirectory(./test)


# --------- Server build ---------

add_executable(rl_server ${SERVER_SRC_FILES} ${COMMON_SRC_FILES})

target_include_directories(rl_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rl_server PUBLIC box2d yaml-cpp)

# copy config file to build directory
file(COPY ${CMAKE_CURRENT_LIST_DIR}/../.rl_config.yml DESTINATION ${CMAKE_BINARY_DIR}/src)

target_compile_options(rl_server PUBLIC
	-Werror
	-Wall
	-O3
	-g
)

# --------- Client build ---------

find_package(Qt5Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_wrap_ui(UIS_HEADERS ${QT_UI_FILES})

add_executable(rocket_league ${CLIENT_SRC_FILES} ${COMMON_SRC_FILES} ${QT_SRC_FILES} ${UIS_HEADERS})

target_include_directories(rocket_league PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# enabling image and font handling
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
SET(SDL2PP_WITH_MIXER YES)

add_subdirectory(../lib/libSDL2pp ../build)

# copy resources to build directory
file(COPY client/assets DESTINATION ${CMAKE_BINARY_DIR}/src)

# adding SDL2pp libary
include_directories(${SDL2PP_INCLUDE_DIRS})
target_link_libraries(rocket_league PUBLIC ${SDL2PP_LIBRARIES})

#include qt
include_directories(${PROJECT_BINARY_DIR})
target_link_libraries(rocket_league PUBLIC Qt5::Widgets)


target_compile_options(rocket_league PUBLIC
	-Werror
	-Wall
	-O3
	-g
)