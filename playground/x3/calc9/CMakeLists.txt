################################################################################
## playground/x3/calc9/CMakeLists.txt
################################################################################

################################################################################
## Spirit.X3 example, EDA concept is based on this. Here, from interested is
## especially why is not there are linker errors. 
################################################################################

project(x3_calc9 LANGUAGES CXX)

## global C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS system)

set(X3_CALC9_SOURCE
    compiler.cpp
    expression.cpp
    main.cpp
    statement.cpp
    vm.cpp
)

add_executable(x3_calc9   EXCLUDE_FROM_ALL ${X3_CALC9_SOURCE})

target_include_directories(x3_calc9 PRIVATE 
    ${EDA_BINARY_ROOT_DIR}/external/src/boost-spirit-x3/include
    ${Boost_INCLUDE_DIR}
)

set(CALC9_TARGET_LINK_LIBRARIES Boost::system)
if(WIN32)
    list(APPEND CALC9_TARGET_LINK_LIBRARIES Boost::filesystem)
endif()    

target_link_libraries(x3_calc9
    PRIVATE ${CALC9_TARGET_LINK_LIBRARIES}
)
