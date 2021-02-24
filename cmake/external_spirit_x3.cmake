message(STATUS "External Project: Boost.Org Spirit Parser X3 - LL(k) Parser Framework")


include(ExternalProject)


# for boost self see https://github.com/arnaudgelas/ExternalProject/blob/master/External-Boost.cmake
ExternalProject_Add(
  external-boost-spirit-x3
  GIT_REPOSITORY        https://github.com/boostorg/spirit.git
  GIT_TAG               boost-1.XX.0
  GIT_PROGRESS          1
  PREFIX                ${CMAKE_BINARY_DIR}/external
  PATCH_COMMAND         ""
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         ""
  INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(boost-spirit-x3 source_dir)
set(EXTERNAL_SPIRIT_X3_INCLUDE_DIR ${source_dir}/include)

