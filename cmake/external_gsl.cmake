message(STATUS "External Project: Guidelines Support Library (GSL)")


include(ExternalProject)


ExternalProject_Add(
  external-gsl
  GIT_REPOSITORY        https://github.com/microsoft/GSL.git
  GIT_TAG               v3.1.0
  GIT_PROGRESS          1
  PREFIX                ${CMAKE_BINARY_DIR}/external
  PATCH_COMMAND         ""
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         ""
  INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(external-gsl source_dir)
set(EXTERNAL_GSL_INCLUDE_DIR ${source_dir}/include)

