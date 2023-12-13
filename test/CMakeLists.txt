include(FetchContent)
include(CTest)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CATCH_INSTALL_HELPERS OFF)
set(CATCH_BUILD_TESTING OFF)
set(CATCH_INSTALL_DOCS OFF)

FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.4.0)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

file(GLOB test-sources CONFIGURE_DEPENDS *.cpp)

include(Catch)

# add c++17 tests
add_executable(${PROJECT_NAME}-tests-17 "${test-sources}")
set_target_properties(${PROJECT_NAME}-tests-17 PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME}-tests-17 PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME})
catch_discover_tests(${PROJECT_NAME}-tests-17)

# add c++20 tests
add_executable(${PROJECT_NAME}-tests-20 "${test-sources}")
set_target_properties(${PROJECT_NAME}-tests-20 PROPERTIES CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME}-tests-20 PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME})
catch_discover_tests(${PROJECT_NAME}-tests-20)