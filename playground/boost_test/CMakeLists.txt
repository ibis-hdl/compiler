################################################################################
# Boost.Test projects
################################################################################

project(bt_playground)


include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(bt_dataset                       EXCLUDE_FROM_ALL bt_dataset.cpp)
