include(FetchContent)
include(CTest)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CATCH_INSTALL_HELPERS OFF)
set(CATCH_BUILD_TESTING OFF)
set(CATCH_INSTALL_DOCS OFF)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

file(GLOB test-sources CONFIGURE_DEPENDS *.cpp)
add_executable(${PROJECT_NAME}-tests "${test-sources}")

target_link_libraries(${PROJECT_NAME}-tests PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME})

include(Catch)
catch_discover_tests(${PROJECT_NAME}-tests)