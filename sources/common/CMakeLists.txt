################################################################################
## souces/common/CMakeLists.txt
################################################################################

################################################################################
## The EDA/common project
################################################################################

project(eda_common LANGUAGES CXX)


project(eda_common LANGUAGES CXX)


set(EDA_COMMON_SOURCE
    src/file_reader.cpp
)


add_library(${PROJECT_NAME} STATIC ${EDA_COMMON_SOURCE})
add_library(eda::common     ALIAS  ${PROJECT_NAME})

# plattform and compiler checks belongs to eda::common, hence the exported 
# ${PROJECT_BINARY_DIR}, generated on top-level CMake file.
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall 
    -Wextra
)


if(CLANG_WARN_EVERYTHING)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Weverything
            -Wno-c++98-compat -Wno-c++98-compat-pedantic
        )
    endif()
endif(CLANG_WARN_EVERYTHING)


## Requirements: Boost headers
find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
