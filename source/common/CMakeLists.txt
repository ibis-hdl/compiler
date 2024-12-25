################################################################################
## IBIS/common project
##
## file: source/common/CMakeLists.txt
################################################################################

project(ibis_common
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_library(${PROJECT_NAME})
add_library(ibis::common ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ibis::util
        Boost::headers
    PRIVATE
        # fmt::fmt
)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/indent_stream.cpp
        src/buildinfo.cpp
        src/file_loader.cpp
        src/settings.cpp
        src/user_home_dir.cpp
        src/message.cpp
)


if(IBIS_ENABLE_CXXSTD_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
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
