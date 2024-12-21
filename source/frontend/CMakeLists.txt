################################################################################
## IBIS/ibis project
##
## file: source/ibis/CMakeLists.txt
################################################################################

project(ibis
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_executable(${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ibis::common
        ibis::color
        ibis::vhdl
        Boost::headers
        Boost::system
        Boost::locale
        CLI11::CLI11
        rollbear::strong_type
        Threads::Threads
        # cope with "fatal error LNK2011: precompiled object not linked in"
        #"$<$<CXX_COMPILER_ID:MSVC>:ibis_pch>"
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ibis/frontend/version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/ibis/frontend/version.hpp
    @ONLY
)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        src/init.cpp
        src/signal_handler.cpp
)


if(IBIS_ENABLE_CXXSTD_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        # PCH, especially G++ requires this, FIXME: 2024 - what was the intention here?
        #$<$<BOOL:${IBIS_ENABLE_PCH_D}>:$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source/vhdl/include>>
)
