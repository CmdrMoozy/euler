find_path(RE2_INCLUDE_DIR re2/re2.h)
find_library(RE2_LIBRARIES NAMES re2)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RE2 DEFAULT_MSG RE2_LIBRARIES RE2_INCLUDE_DIR)
mark_as_advanced(RE2_INCLUDE_DIR RE2_LIBRARIES)
