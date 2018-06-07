################################################################################
## souces/common/CMakeLists.txt
################################################################################

################################################################################
## The EDA/common project
################################################################################

project(eda_common LANGUAGES CXX)


## create a dummy header-only target
add_library(${PROJECT_NAME} INTERFACE)
add_library(eda::common ALIAS ${PROJECT_NAME})

target_include_directories(eda_common INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


## Requirements: Boost headers
find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

