################################################################################
## IBIS/common project
##
## file: source/common/CMakeLists.txt
################################################################################

project(ibis_common LANGUAGES CXX)


add_library(${PROJECT_NAME})
add_library(ibis::common ALIAS ${PROJECT_NAME})


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
        $<$<BOOL:${WIN32}>:src/color_platform_windows.cpp>
        src/user_home_dir.cpp
)


# Platform and compiler checks
include(configure_platform_hpp)
include(configure_config_hpp)


target_precompile_headers(${PROJECT_NAME}
    PRIVATE
        $<$<BOOL:${IBIS_ENABLE_PCH_STD}>:${PROJECT_SOURCE_DIR}/include/ibis/detail/pch.hpp>
        $<$<BOOL:${IBIS_ENABLE_PCH_BOOST}>:${PROJECT_SOURCE_DIR}/include/ibis/detail/pch_boost.hpp>
        $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:${PROJECT_SOURCE_DIR}/include/ibis/detail/pch_prj.hpp>
)


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)


configure_file(
    "${PROJECT_SOURCE_DIR}/include/ibis/buildinfo_static.hpp.in"
    "${PROJECT_BINARY_DIR}/include/ibis/buildinfo_static.hpp"
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
