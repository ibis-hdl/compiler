################################################################################
## IBIS/color project
##
## file: source/color/CMakeLists.txt
################################################################################

project(ibis_color LANGUAGES CXX)


add_library(${PROJECT_NAME})
add_library(ibis::color ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ibis::util
)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/color.cpp
        $<$<BOOL:${WIN32}>:src/color_platform_windows.cpp>
)


if(${PROJECT_NAME}_PCH)
    # override ibis_pch helper
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<$<BOOL:${IBIS_ENABLE_PCH_DEFAULT}>:${PROJECT_SOURCE_DIR}/include/ibis/color/detail/pch_default.hpp>
            $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:${PROJECT_SOURCE_DIR}/include/ibis/color/detail/pch_ibis.hpp>
    )
elseif(IBIS_ENABLE_PCH_DEFAULT OR IBIS_ENABLE_PCH_IBIS)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)
