################################################################################
## playground/boost_test/MakeLists.txt
################################################################################

################################################################################
# Boost.Test scratchpad projects
################################################################################

project(bt_playground)


# concept test for data_set tests
add_executable(bt_dataset                       EXCLUDE_FROM_ALL bt_dataset.cpp)



################################################################################
##
# Boost.UTF Issue: 
# - [access to master_test_suite().{argc, argv}](
#    https://svn.boost.org/trac10/ticket/12953)
# - [[Boost.Test] access to boost::unit_test::framework::master_test_suite().{argc, argv} outside from BOOST_TEST](
#    https://groups.google.com/forum/#!topic/boost-developers-archive/wtnY9F2cWNI)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# Concept
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

# Issue source
add_executable(bt_issue12953 EXCLUDE_FROM_ALL
    dataset_master_test_suite_accessible_main.cpp
    dataset_master_test_suite_accessible_test.cpp
    dataset_master_test_suite_accessible_test_with_arity.cpp
)
add_dependencies(bt_issue12953 boost-utf)
target_include_directories(bt_issue12953 PRIVATE
    $<BUILD_INTERFACE:${BOOST_UTF_INCLUDE_DIR}>
)
target_link_libraries(bt_issue12953
    PRIVATE
    Boost::system
    Boost::filesystem
)

#add_test(NAME boost_test_issue12953
#    COMMAND bt_issue12953 -- --param1=1 --param2=2
#)
