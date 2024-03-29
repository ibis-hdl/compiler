## -----------------------------------------------------------------------------
## prevent in-source cmake builds
## -----------------------------------------------------------------------------

function(prevent_in_source_builds)
  # make sure the user doesn't play dirty with symlinks
  get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
  get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

  # disallow in-source builds
  if("${srcdir}" STREQUAL "${bindir}")
    message("############################################################")
    message("# You should not configure & build in the source directory #")
    message("############################################################")
    # see [Prohibit cmake build on the top-level source](
    # https://stackoverflow.com/questions/73083662/prohibit-cmake-build-on-the-top-level-source)
    message("Please clean up the CMakeFiles/ directory and CMakeCache.txt file.")
    message(FATAL_ERROR "Quitting configuration")
  endif()
endfunction()

prevent_in_source_builds()
