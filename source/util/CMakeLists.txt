################################################################################
## IBIS/util project
##
## Just for curiosity: [Windows 10 Still Won’t Let You Use These File Names Reserved in 1974](
## https://www.howtogeek.com/fyi/windows-10-still-wont-let-you-use-these-file-names-reserved-in-1974/)
##
## file: source/util/CMakeLists.txt
################################################################################

project(ibis_util
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")

add_library(${PROJECT_NAME} INTERFACE)
add_library(ibis::util ALIAS ${PROJECT_NAME})


if(IBIS_ENABLE_CXXSTD_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Boost::headers
        fmt::fmt    # FixMe [CMake]: Even not required, MSVC PCH errors due to /utf-8 compile flag
        Boost::unit_test_framework  # FixMe [CMake]: ibis::util shouldn't be depend on Boost::Utf
)
