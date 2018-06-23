################################################################################
## playground/boost_test/MakeLists.txt
################################################################################

################################################################################
# Boost.Test scratchpad projects
################################################################################

project(bt_playground)


# concept test for data_set tests
add_executable(bt_dataset                       EXCLUDE_FROM_ALL bt_dataset.cpp)


# Issue:
# - [[Boost.Test] access to boost::unit_test::framework::master_test_suite().{argc, argv} outside from BOOST_TEST](
#    https://groups.google.com/forum/#!topic/boost-developers-archive/wtnY9F2cWNI)
# - [access to master_test_suite().{argc, argv}](
#    https://svn.boost.org/trac10/ticket/12953)
find_package(Boost REQUIRED COMPONENTS system filesystem)
add_executable(bt_dataset_args                  EXCLUDE_FROM_ALL bt_dataset_args.cpp)
add_dependencies(bt_dataset_args boost-utf)
target_include_directories(bt_dataset_args PRIVATE
    $<BUILD_INTERFACE:${BOOST_UTF_INCLUDE_DIR}>
)
target_link_libraries(bt_dataset_args
    PRIVATE
    Boost::system
    Boost::filesystem
)
