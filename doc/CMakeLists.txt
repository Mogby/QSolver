find_package(Doxygen REQUIRED)

set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/doc)

# Prevent doxygen from showing macro definitions
# because they are super ugly.
set(DOXYGEN_MAX_INITIALIZER_LINES 0)

doxygen_add_docs(doc
    ${PROJECT_SOURCE_DIR}/doc/groups.hpp
    ${PROJECT_SOURCE_DIR}/include
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
