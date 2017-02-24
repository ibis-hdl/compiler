message("External project: C++ Guideline Support Library (Microsoft/GSL)")

ExternalProject_Add(
    gsl
    GIT_REPOSITORY        https://github.com/Microsoft/GSL.git
    GIT_TAG               master
    PREFIX                ${PROJECT_BINARY_DIR}/external
    CONFIGURE_COMMAND     ""
    BUILD_COMMAND         ""
    INSTALL_COMMAND       ""
)

ExternalProject_Get_Property(gsl source_dir)
set(GSL_INCLUDE_DIR ${source_dir}/include)
