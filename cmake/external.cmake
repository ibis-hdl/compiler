message(STATUS "External Projects (required)")

## ----------------------------------------------------------------------------
# External dependencies

##
# CLI11
CPMAddPackage("gh:CLIUtils/CLI11#v1.9.1")
add_custom_target(external-cli11)
set(CLI11_INCLUDE_DIR ${CLI11_SOURCE_DIR}/include)
