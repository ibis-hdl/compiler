message(STATUS "External Project: CLIUtils/CLI11 Command line parser for C++11")


include(ExternalProject)



ExternalProject_Add(
  external-cli11
  GIT_REPOSITORY        https://github.com/CLIUtils/CLI11.git
  GIT_TAG               master
  GIT_PROGRESS          1
  PREFIX                ${CMAKE_BINARY_DIR}/external
  PATCH_COMMAND         ""
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         ""
  INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(external-cli11 source_dir)
set(CLI11_INCLUDE_DIR ${source_dir}/include)

