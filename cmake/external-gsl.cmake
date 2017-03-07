message("External project: C++ Guideline Support Library (Microsoft/GSL)")



ExternalProject_Add(
  gsl
  GIT_REPOSITORY        https://github.com/Microsoft/GSL.git
  GIT_TAG               master
  PREFIX                ${PROJECT_BINARY_DIR}/external
  PATCH_COMMAND         ""
  CONFIGURE_COMMAND     ""
  BUILD_COMMAND         ""
  INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(gsl source_dir)
set(GSL_INCLUDE_DIR ${source_dir}/include)


# create a .no_backup file for bacula
ExternalProject_Get_Property(gsl PREFIX)

ExternalProject_Add_Step(
  gsl
  tag_no_backup
  COMMAND              touch ${PREFIX}/.no_backup
) 

