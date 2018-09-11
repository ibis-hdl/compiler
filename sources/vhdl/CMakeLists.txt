################################################################################
## sources/vhdl/CMakeLists.txt
################################################################################

################################################################################
## EDA/VHDL project
################################################################################

project(eda_vhdl_parser LANGUAGES CXX)


add_library(${PROJECT_NAME} "")
add_library(eda::vhdl_parser ALIAS ${PROJECT_NAME})


# Ninja Build
set_property(TARGET eda_vhdl_parser PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


add_dependencies(${PROJECT_NAME} boost-spirit-x3)


target_sources(${PROJECT_NAME} PRIVATE
    src/ast/literal_printer.cpp
    src/ast/keyword_token.cpp
    src/ast/operator_token.cpp
    src/ast/ast_printer.cpp
    src/ast/ast_stats.cpp
    src/ast/numeric_convert.cpp
    src/ast/position_cache.cpp
    
    src/parser/error_handler.cpp
    src/parser/on_error_base.cpp
    src/parser/grammar.cpp
    src/parser/parse.cpp
    
    src/analyze/error_handler.cpp
    src/analyze/check/label_match.cpp
    src/analyze/syntax.cpp
    
    src/context.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${SPIRIT_X3_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)


if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE
		/W1
	)
	# [#define NOMINMAX using std::min/max}(
	#  https://stackoverflow.com/questions/13416418/define-nominmax-using-stdmin-max)
	target_compile_definitions(${PROJECT_NAME} PUBLIC
		NOMINMAX
	)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE
		-Wall 
		-Wextra
	)
endif()


##
# MSYS2/MinGW64 has problems with spirit.x3 (doesn't help really)
if(WIN32 AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_source_files_properties(
        src/parser/grammar.cpp
        PROPERTIES COMPILE_FLAGS 
            -Wa,-mbig-obj
    )
endif()
    

##
# Clang -Weverything
if(CLANG_WARN_EVERYTHING)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Weverything
            -Wno-c++98-compat -Wno-c++98-compat-pedantic
            -Wno-padded
        )
    
        set_source_files_properties(
            src/ast/literal_printer.cpp 
            src/ast/keyword_token.cpp
            src/ast/operator_token.cpp
            PROPERTIES COMPILE_FLAGS 
                -Wno-covered-switch-default
        )
        
        set_source_files_properties(
            src/parser/grammar.cpp
            PROPERTIES COMPILE_FLAGS 
                "-Wno-disabled-macro-expansion -Wno-global-constructors -Wno-exit-time-destructors"
        )
    endif()
endif(CLANG_WARN_EVERYTHING)


# limit gcc/clang template error depth printing
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ftemplate-backtrace-limit=0
    )
endif()


# increase limit for clang recursive template instantiation
# otherwise exceedes maximum depth of 256
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE -ftemplate-depth=1024)
endif()


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::common
)
