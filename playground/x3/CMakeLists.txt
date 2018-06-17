################################################################################
## playground/x3/CMakeLists.txt
################################################################################

################################################################################
# Spirit.X3 scratchpad projects
################################################################################

project(x3_playground)

find_package(Boost REQUIRED system filesystem)


# default/common error handling of Spirit.x3
add_executable(x3_common_error_handler EXCLUDE_FROM_ALL x3_common_error_handler.cpp)
target_include_directories(x3_common_error_handler PRIVATE 
    ${SPIRIT_X3_INCLUDE_DIR}
)
target_link_libraries(x3_common_error_handler
    PRIVATE
    Boost::system
    Boost::filesystem   # for MinGW/Windows
)

# concept of recovering from parser error
add_executable(x3_handle_parse_error EXCLUDE_FROM_ALL x3_handle_parse_error.cpp)
target_include_directories(x3_handle_parse_error PRIVATE 
    ${SPIRIT_X3_INCLUDE_DIR}
)
target_link_libraries(x3_handle_parse_error
    PRIVATE
    Boost::system
    Boost::filesystem   # for MinGW/Windows
)

# original example from Spirit.x3 to check ominous linker error seen here
add_subdirectory(calc9)
