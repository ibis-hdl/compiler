################################################################################
## sources/vhdl/CMakeLists.txt
################################################################################

################################################################################
## EDA/VHDL project
################################################################################

project(eda_vhdl_parser LANGUAGES CXX)


set(VHDL_PARSER_SOURCE
    src/ast/literal_printer.cpp
    src/ast/keyword_token.cpp
    src/ast/operator_token.cpp
    src/ast/ast_printer.cpp
    src/ast/numeric_convert.cpp
    
    src/parser/error_handler.cpp

    #src/parser/grammar.cpp
)

add_library(${PROJECT_NAME} STATIC ${VHDL_PARSER_SOURCE})
add_library(eda::vhdl_parser ALIAS ${PROJECT_NAME})


# adjust include path
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)


target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall 
    -Wextra
)


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


## Boost.Org 
# Spirit X3 is required for the parser - we are working on developer branch. 
# Nevertheless Spirit self depends on other headers, e..g boost.range
find_package(Boost)

# depend on newer Spirit.X3 versions
add_dependencies(${PROJECT_NAME} boost-spirit-x3)

# Boost.Org depend includes
include_directories(${SPIRIT_X3_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})


# Depencies
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::common
)


## doc, etc.
add_subdirectory(doc)


## Install targets
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE  DESTINATION ${PROJECT_NAME}
    LIBRARY  DESTINATION ${PROJECT_NAME}
    RUNTIME  DESTINATION ${PROJECT_NAME})  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

install(EXPORT ${PROJECT_NAME}Config
    DESTINATION share/cmake/${PROJECT_NAME}Config)

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)


