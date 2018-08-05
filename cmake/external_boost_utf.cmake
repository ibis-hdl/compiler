message(STATUS "External Project: Boost.Org Unit Test Framework (UTF)")


include(ExternalProject)


# see [access to master_test_suite().{argc, argv}](
# https://svn.boost.org/trac10/ticket/12953)
ExternalProject_Add(
  boost-utf
  GIT_REPOSITORY        https://github.com/boostorg/test.git
  GIT_TAG               topic/12953-access-master_test_suite-in-datatest-cases
  #GIT_TAG               boost-1.67.0
  GIT_PROGRESS          1
  PREFIX                ${CMAKE_BINARY_DIR}/external
  PATCH_COMMAND         ""
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         ""
  INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(boost-utf source_dir)
set(BOOST_UTF_INCLUDE_DIR ${source_dir}/include)


# create a .no_backup file for bacula
ExternalProject_Get_Property(boost-utf PREFIX)
ExternalProject_Add_Step(
  boost-utf
  tag_no_backup
  COMMAND              echo > ${PREFIX}/.no_backup
)

