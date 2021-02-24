message(STATUS "External Project: Boost.Org Unit Test Framework (UTF)")


include(ExternalProject)


ExternalProject_Add(
  external-boost-utf
  GIT_REPOSITORY        https://github.com/boostorg/test.git
  GIT_TAG               boost-1.XX.0
  GIT_PROGRESS          1
  PREFIX                ${CMAKE_BINARY_DIR}/external
  PATCH_COMMAND         ""
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         ""
  INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(boost-utf source_dir)
set(EXTERNAL_BOOST_UTF_INCLUDE_DIR ${source_dir}/include)

