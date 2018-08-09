################################################################################
## souces/common/CMakeLists.txt
################################################################################

################################################################################
## The EDA/common project
################################################################################

project(eda_common LANGUAGES CXX)


set(EDA_COMMON_SOURCE
    src/file_reader.cpp
    src/settings.cpp
    src/winapi_color.cpp
)


add_library(${PROJECT_NAME} STATIC ${EDA_COMMON_SOURCE})
add_library(eda::common     ALIAS  ${PROJECT_NAME})

# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


##
# Plattform and compiler checks
include(build_config_hpp)


# plattform and compiler checks belongs to eda::common, hence the exported 
# ${PROJECT_BINARY_DIR}, generated on top-level CMake file.
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE ${DOCOPT_CPP_DIR}
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
find_package(Boost REQUIRED filesystem)
target_link_libraries(${PROJECT_NAME}
	Boost::filesystem
)

##
# Windows MinGW
# [How to fix undefined reference to `__imp_WSACleanup' (Boost.Asio) in CLion](
#  https://stackoverflow.com/questions/38767653/how-to-fix-undefined-reference-to-imp-wsacleanup-boost-asio-in-clion)
if(MINGW)
	target_link_libraries(${PROJECT_NAME}
   		ws2_32
	)
endif()
