include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE COMMON_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../common/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../common/*.h)
file(GLOB_RECURSE TEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

enable_testing()

add_executable(
  protocol_test
  protocol_test.cc
  ${COMMON_SRC_FILES}
  ${TEST_SRC_FILES}
)
target_link_libraries(
  protocol_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(protocol_test)