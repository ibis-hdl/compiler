################################################################################
## IBIS/testsuite util utils project
##
## file: testsuite/util/CMakeLists.txt
################################################################################

project(testrunner_util
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_executable(${PROJECT_NAME})


add_test(NAME test_util
    COMMAND
        ${PROJECT_NAME} --log_level=error
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ibis::util
        Boost::headers
        Boost::unit_test_framework
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


target_sources(${PROJECT_NAME}
    PRIVATE
        src/test_util.cpp
        # concrete test cases
        src/test/trim_sv_test.cpp
        src/test/tokenize_test.cpp
)


#set_source_files_properties(src/test_util.cpp
#    APPEND PROPERTIES
#        # Failed to link Boost UTF with Windows/Clang, Linux works
#        COMPILE_DEFINITIONS "$<$<NOT:$<PLATFORM_ID:Windows>>:BOOST_TEST_DYN_LINK>"
#)

# [Boost.Test linker error by use with precompiled headers (PCH)](
#  https://stackoverflow.com/questions/66535719/boost-test-linker-error-by-use-with-precompiled-headers-pch)
set_source_files_properties(src/test_util.cpp
    PROPERTIES
        SKIP_PRECOMPILE_HEADERS ON
)


if (IBIS_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE

    )
endif()


target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)


# FixMe: on Windows, mt.exe failed to write the updated manifest to the resource
# The settings below doesn't solve the problem ... Simply restart compiling.
if(WIN32)
    set_property(TARGET ${PROJECT_NAME}
        PROPERTY
            JOB_POOL_COMPILE    NINJA_JOBS_SINGLE_CORE
    )
    set_property(TARGET ${PROJECT_NAME}
        PROPERTY
            JOB_POOL_LINK       NINJA_JOBS_SINGLE_CORE
    )
endif()
