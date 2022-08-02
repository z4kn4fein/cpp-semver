cmake_minimum_required(VERSION 3.22)
project(semver
        LANGUAGES CXX
        VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(${PROJECT_NAME} INTERFACE)
if (NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    add_library (${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
endif()

target_include_directories(
        ${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if (SEMVER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

if (SEMVER_INSTALL)
    configure_package_config_file(
            "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
            INSTALL_DESTINATION "share/cmake/${PROJECT_NAME}
            PATH_VARS ${CMAKE_INSTALL_INCLUDEDIR}")

    write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion)

    install(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}-targets
            INCLUDES DESTINATION "${CMAKE_INSTALL_DATADIR}")

    install(EXPORT ${PROJECT_NAME}-targets
            DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}"
            NAMESPACE ${PROJECT_NAME}::
            FILE "${PROJECT_NAME}-targets.cmake")

    install(FILES
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
            DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}")

    install(DIRECTORY "include/" TYPE INCLUDE)
endif()