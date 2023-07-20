cmake_minimum_required(VERSION 3.20)

project(GlslShaderIncluder)

set(BUILD_DIRECTORY_NAME OUTPUT)

# Add project lib.
set(PROJECT_LIB_DIRECTORY project_lib)
message(STATUS "Adding target ${PROJECT_LIB_DIRECTORY}...")
add_subdirectory(src/${PROJECT_LIB_DIRECTORY} ${BUILD_DIRECTORY_NAME}/${PROJECT_LIB_DIRECTORY})

# Add project tests target.
set(PROJECT_TESTS_DIRECTORY project_tests)
message(STATUS "Adding target ${PROJECT_LIB_DIRECTORY}...")
add_subdirectory(src/${PROJECT_TESTS_DIRECTORY} ${BUILD_DIRECTORY_NAME}/${PROJECT_TESTS_DIRECTORY})