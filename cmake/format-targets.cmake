set(
    FORMAT_PATTERNS
    source/*.cpp source/*.hpp
    include/*.hpp
    test/*.cpp test/*.hpp
    CACHE STRING
    "separated patterns relative to the project source dir to format."
)

set(FORMAT_COMMAND clang-format CACHE STRING "; Formatter to use.")

add_custom_target(
    format-check
    COMMAND "${CMAKE_COMMAND}"
    -D "FORMAT_COMMAND=${FORMAT_COMMAND}"
    -D "PATTERNS=${FORMAT_PATTERNS}"
    -P "${PROJECT_SOURCE_DIR}/cmake/format.cmake"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Linting the code for format issues."
    VERBATIM
)

add_custom_target(
    format-fix
    COMMAND "${CMAKE_COMMAND}"
    -D "FORMAT_COMMAND=${FORMAT_COMMAND}"
    -D "PATTERNS=${FORMAT_PATTERNS}"
    -D FIX_FORMAT_ISSUES=YES
    -P "${PROJECT_SOURCE_DIR}/cmake/format.cmake"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Fixing formatting code issues."
    VERBATIM
)
