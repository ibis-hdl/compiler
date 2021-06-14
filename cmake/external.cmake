message(STATUS "External Projects (required)")

## ----------------------------------------------------------------------------
# mandatory external dependencies

##
# CLI11
CPMAddPackage("gh:CLIUtils/CLI11#v1.9.1")
add_custom_target(external-cli11)
set(CLI11_INCLUDE_DIR ${CLI11_SOURCE_DIR}/include)

##
# strong_type
CPMAddPackage("gh:rollbear/strong_type#main")
add_custom_target(external-strong_type)
set(STRONG_TYPE_INCLUDE_DIR ${strong_type_SOURCE_DIR}/include)
