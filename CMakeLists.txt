cmake_minimum_required(VERSION 3.22)
project(semver LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

option(SEMVER_BUILD_TESTS "Enable builds of tests" ON)

include(GNUInstallDirs)

## --------------------------------------------------------------------
## Build
## --------------------------------------------------------------------
message(PROJECT_NAME: ${PROJECT_NAME})
message(CMAKE_HOST_SYSTEM: ${CMAKE_HOST_SYSTEM})
message(CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE})
message(CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER})
message(CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID})
message(CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION})
message(CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS})

add_library(${PROJECT_NAME} INTERFACE)
add_library (${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(
        ${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

## --------------------------------------------------------------------
## TESTS
## --------------------------------------------------------------------
if (SEMVER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

## --------------------------------------------------------------------
## INSTALL
## --------------------------------------------------------------------
include(CMakePackageConfigHelpers)

configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}
        PATH_VARS CMAKE_INSTALL_FULL_INCLUDEDIR)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}${PROJECT_NAME}-config-version.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
        DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME})

export(TARGETS ${PROJECT_NAME}
       NAMESPACE ${PROJECT_NAME}::
       FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-targets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${PROJECT_NAME}-targets
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME})