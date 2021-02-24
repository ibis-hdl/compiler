################################################################################
## playground/cli11/CMakeLists.txt
################################################################################

project(cli11_playground)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

find_package(Boost 1.73.0 REQUIRED COMPONENTS 
    locale
)

add_executable(cli11_161        EXCLUDE_FROM_ALL cli11.cpp)
target_include_directories(cli11_161
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/CLI11_v161
)
target_link_libraries(cli11_161
    PUBLIC
        Boost::locale
)


add_executable(cli11_191        EXCLUDE_FROM_ALL cli11.cpp)
target_include_directories(cli11_191
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/CLI11_v191
)
target_link_libraries(cli11_191
    PUBLIC
        Boost::locale
)
