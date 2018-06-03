################################################################################
## playground/x3/calc9/CMakeLists.txt
################################################################################

################################################################################
## Spirit.X3 example, EDA concept is based on this. Here, from interested is
## especially why is not there are linker errors. 
################################################################################

project(x3_calc9 LANGUAGES CXX)

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

target_link_libraries(x3_calc9
    PRIVATE
    ${Boost_SYSTEM_LIBRARY}
)
