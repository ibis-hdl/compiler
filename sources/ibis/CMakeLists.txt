################################################################################
## sources/ibis/CMakeLists.txt
################################################################################

################################################################################
## EDA/VHDL project
################################################################################

project(ibis LANGUAGES CXX)


set(IBIS_SOURCE
    src/docopt_inst.cpp
    src/parse_cli.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${IBIS_SOURCE})

##
# DocOpt++
# parsing command line 
include(external_docopt_cpp)
include_directories(${DOCOPT_CPP_DIR})


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE ${DOCOPT_CPP_DIR}
)


target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall 
    -Wextra
)


if(CLANG_WARN_EVERYTHING)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Weverything
            -Wno-c++98-compat -Wno-c++98-compat-pedantic
        )
    endif()
endif(CLANG_WARN_EVERYTHING)


# limit gcc/clang template error depth printing
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ftemplate-backtrace-limit=0
    )
endif()


##
# DocOpt++
add_dependencies(${PROJECT_NAME} docopt_cpp)


## 
# Boost.Org Libraries
find_package(Boost REQUIRED COMPONENTS 
    system locale 
    filesystem
)


# Depencies
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::common
    Boost::system
    Boost::locale
    Boost::filesystem
)

