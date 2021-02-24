################################################################################
## EDA/testsuite VHDL syntax project
##
## file: testsuite/vhdl/syntax/CMakeLists.txt
################################################################################

project(testrunner_vhdl_syntax LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")


if(EDA_EXTERNAL_BOOST_UTF)
    add_dependencies(${PROJECT_NAME} external-boost-utf)
endif()


target_sources(${PROJECT_NAME} PRIVATE
    src/common/test_vhdl_syntax.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    src/label_check_test.cpp
    src/keyword_match_test.cpp
)


if (EDA_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME} 
        PRIVATE 
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/syntax/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/syntax/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${EXTERNAL_BOOST_UTF_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)


target_compile_definitions(${PROJECT_NAME} PRIVATE
    # don't allow automatically select which libraries to link against    
    $<$<CXX_COMPILER_ID:MSVC>:BOOST_ALL_NO_LIB>
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl_parser
    testsuite::common
    Boost::system
    Boost::filesystem
    Boost::locale
)


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Boost::unit_test_framework 
    )
endif()


## 
# CMake/CTest
# The argument is the top level directory of the test directories of 'test_case'
add_test(NAME test_vhdl_syntax
    COMMAND ${PROJECT_NAME} -- 
    --source-dir=${PROJECT_SOURCE_DIR}
    --destination-dir=${PROJECT_BINARY_DIR}
    --input-extension=.vhdl
#    --write-extension=.result    
    --write-extension=.expected    
)
