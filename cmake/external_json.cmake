message(STATUS "External Project: RapidJSON parser/generator for C++ with both SAX/DOM style API")


include(ExternalProject)



ExternalProject_Add(
  RapidJSON
  GIT_REPOSITORY        https://github.com/Tencent/rapidjson.git
  GIT_TAG               master
  GIT_PROGRESS          1
  PREFIX                ${CMAKE_BINARY_DIR}/external
  PATCH_COMMAND         ""
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         ""
  INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(RapidJSON source_dir)
set(RapidJSON_INCLUDE_DIR ${source_dir}/include)


# create a .no_backup file for bacula
ExternalProject_Get_Property(RapidJSON PREFIX)
ExternalProject_Add_Step(
  RapidJSON
  tag_no_backup
  COMMAND              echo > ${PREFIX}/.no_backup
)

