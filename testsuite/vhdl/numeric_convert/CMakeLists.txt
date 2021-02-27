################################################################################
## EDA/testsuite VHDL numeric convert project
##
## file: testsuite/vhdl/numeric_convert/CMakeLists.txt
################################################################################

project(testrunner_vhdl_numeric_convert LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")


add_test(NAME test_vhdl_numeric_conversion
    COMMAND 
        ${PROJECT_NAME}
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        eda::vhdl_parser
        testsuite::common
        Boost::system
        Boost::filesystem
        Boost::locale
        Boost::unit_test_framework 
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


if(EDA_EXTERNAL_BOOST_SPIRIT_X3)
    add_dependencies(${PROJECT_NAME} boost-spirit-x3)
endif()
if(EDA_EXTERNAL_BOOST_UTF)
    add_dependencies(${PROJECT_NAME} boost-utf)
endif()


target_sources(${PROJECT_NAME} 
    PRIVATE
        src/common/test_numeric_convert.cpp
        src/common/numeric_parser.cpp
        src/common/binary_string.cpp
        # concrete test cases
        src/bit_string_literal_test.cpp
        src/decimal_literal_test.cpp
        src/based_literal_test.cpp
)



set_source_files_properties(src/common/test_numeric_convert.cpp
    APPEND PROPERTIES 
        COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK" 
)


if (EDA_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME} 
        PRIVATE 
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl_numeric_convert/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl_numeric_convert/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME} 
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_SPIRIT_X3_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_UTF_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)


target_compile_definitions(${PROJECT_NAME} 
    PRIVATE
        # don't allow automatically select which libraries to link against    
        $<$<CXX_COMPILER_ID:MSVC>:BOOST_ALL_NO_LIB>
)
