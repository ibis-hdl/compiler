message("External Project: DocOpt++")


include(ExternalProject)


ExternalProject_Add(
  docopt_cpp
  GIT_REPOSITORY        https://github.com/docopt/docopt.cpp.git
  GIT_TAG               master
  GIT_PROGRESS          1
  PREFIX                ${PROJECT_BINARY_DIR}/external
  PATCH_COMMAND         ""
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         ""
  INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(docopt_cpp source_dir)
set(DOCOPT_CPP_DIR ${source_dir})


# create a .no_backup file for bacula
ExternalProject_Get_Property(docopt_cpp PREFIX)
ExternalProject_Add_Step(
  docopt_cpp
  tag_no_backup
  COMMAND              echo > ${PREFIX}/.no_backup
)

