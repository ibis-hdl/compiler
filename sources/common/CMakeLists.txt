################################################################################
## EDA/common project
##
## file: sources/common/CMakeLists.txt
################################################################################

project(eda_common LANGUAGES CXX)


add_library(${PROJECT_NAME} "")
add_library(eda::common     ALIAS  ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        # nothings
)


target_sources(${PROJECT_NAME} 
    PRIVATE
        src/buildinfo.cpp
        src/file_loader.cpp
        src/settings.cpp
        src/color.cpp
        src/winapi_color.cpp ### FixMe: looks strange on Linux, but is correct so far
        src/user_home.cpp
)


# Platform and compiler checks
include(configure_platform_hpp)
include(configure_config_hpp)


if (EDA_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME} 
        PRIVATE 
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/eda/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/eda/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME} 
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)


configure_file(
    "${PROJECT_SOURCE_DIR}/include/eda/buildinfo_static.hpp.in"
    "${PROJECT_BINARY_DIR}/include/eda/buildinfo_static.hpp"
    ESCAPE_QUOTES
    @ONLY
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
