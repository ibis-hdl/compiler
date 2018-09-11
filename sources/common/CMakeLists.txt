################################################################################
## souces/common/CMakeLists.txt
################################################################################

################################################################################
## The EDA/common project
################################################################################

project(eda_common LANGUAGES CXX)


add_library(${PROJECT_NAME} "")
add_library(eda::common     ALIAS  ${PROJECT_NAME})


# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


target_sources(${PROJECT_NAME} PRIVATE
    src/file_reader.cpp
    src/settings.cpp
    src/color.cpp
    src/winapi_color.cpp
    src/user_home.cpp
)


# Plattform and compiler checks
include(build_config_hpp)


# plattform and compiler checks belongs to eda::common, hence the exported 
# ${PROJECT_BINARY_DIR}, generated on top-level CMake file.
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)


if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE
		/W1
	)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE
		-Wall 
		-Wextra
	)
endif()


if(CLANG_WARN_EVERYTHING)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Weverything
            -Wno-c++98-compat -Wno-c++98-compat-pedantic
        )
    endif()
endif(CLANG_WARN_EVERYTHING)


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
