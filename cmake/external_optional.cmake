message(STATUS "External Projects (optional)")

## -----------------------------------------------------------------------------
# Bleeding Edge external Boost dependencies
#
# Sometimes installed packages are too old, so we can enable bleeding edge boost libs

##
# Boost Spirit
option(DEVELOPER_EXTERNAL_BOOST_SPIRIT
    "Configure IBIS HDL to use external Boost.Org Spirit Parser X3 - LL(k) Parser Framework.\
    This is useful for developers which has to work on more recent versions\
    as the build host/system supplies."
    OFF)
mark_as_advanced(DEVELOPER_EXTERNAL_BOOST_SPIRIT)

if(DEVELOPER_EXTERNAL_BOOST_SPIRIT)
    CPMAddPackage(
            NAME external-boost-spirit
            GITHUB_REPOSITORY boostorg/spirit
            GIT_TAG boost-1.76.0
            OPTIONS "BUILD_TESTING OFF"
    )
    if(external-boost-spirit_ADDED)
        add_custom_target(external-boost-spirit)
        set(EXTERNAL_BOOST_SPIRIT_INCLUDE_DIR
            ${boost_spirit_SOURCE_DIR}/include CACHE PATH "" FORCE
        )
    else()
        message(FATAL_ERROR "Failure in external Boost's optional module 'Spirit'")
    endif()
endif()


##
# Boost Test
option(DEVELOPER_EXTERNAL_BOOST_TEST
    "Configure IBIS HDL to use external Boost.Org Unit Test Framework (UTF).\
    This is useful for developers which has to work on more recent versions\
    as the build host/system supplies."
    OFF)
mark_as_advanced(DEVELOPER_EXTERNAL_BOOST_TEST)

if(DEVELOPER_EXTERNAL_BOOST_TEST)
    CPMAddPackage(
        NAME external-boost-test
        GITHUB_REPOSITORY boostorg/test
        GIT_TAG boost-1.76.0
        # no OPTIONS, since isn't CMake ready
    )
    if(external-boost-test_ADDED)
        add_custom_target(external-boost-test)
        set(EXTERNAL_BOOST_TEST_INCLUDE_DIR
            ${external-boost-test_SOURCE_DIR}/include CACHE PATH "" FORCE
        )
    else()
        message(FATAL_ERROR "Failure in external Boost's optional module 'Test'")
    endif()
endif()
