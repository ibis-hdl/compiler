################################################################################
## EDA/testsuite VHDL AST project
##
## file: testsuite/vhdl/ast/CMakeLists.txt
################################################################################

project(testrunner_vhdl_ast LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")


add_test(NAME test_ast
    COMMAND 
        ${PROJECT_NAME} -- 
        --source-dir=${PROJECT_SOURCE_DIR}/test_case
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        eda::vhdl_parser
        testsuite::common
        Boost::system
        Boost::filesystem
        Boost::unit_test_framework 
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


if(EDA_EXTERNAL_BOOST_UTF)
    add_dependencies(${PROJECT_NAME} external-boost-utf)
endif()


target_sources(${PROJECT_NAME} 
    PRIVATE
        src/common/test_ast.cpp
        src/common/position_cache_fixture.cpp
        # concrete test cases
        src/position_cache_test_1.cpp
        src/position_cache_test_2.cpp
        src/literal_printer_test.cpp
)


set_source_files_properties(src/common/test_ast.cpp
    APPEND PROPERTIES 
        COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK" 
)


if (EDA_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME} 
        PRIVATE 
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/ast/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/ast/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME} 
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_UTF_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)


target_compile_definitions(${PROJECT_NAME} 
    PRIVATE
        # don't allow automatically select which libraries to link against    
        $<$<CXX_COMPILER_ID:MSVC>:BOOST_ALL_NO_LIB>
)


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE
            Boost::unit_test_framework 
    )
endif()
