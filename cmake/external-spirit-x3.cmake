message("External project: boost.org spirit parser X3 LL(k) parser framework")


include(ExternalProject)


# for boost self see https://github.com/arnaudgelas/ExternalProject/blob/master/External-Boost.cmake
ExternalProject_Add(
  boost-spirit-x3
  GIT_REPOSITORY        https://github.com/boostorg/spirit.git
  GIT_TAG               boost-1.64.0
#  GIT_TAG               develop
  PREFIX                ${EDA_BINARY_ROOT_DIR}/external
  PATCH_COMMAND         ""
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         ""
  INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(boost-spirit-x3 source_dir)
set(SPIRIT_X3_INCLUDE_DIR ${source_dir}/include)


# create a .no_backup file for bacula
ExternalProject_Get_Property(boost-spirit-x3 PREFIX)

ExternalProject_Add_Step(
  boost-spirit-x3
  tag_no_backup
  COMMAND              touch ${PREFIX}/.no_backup
)

