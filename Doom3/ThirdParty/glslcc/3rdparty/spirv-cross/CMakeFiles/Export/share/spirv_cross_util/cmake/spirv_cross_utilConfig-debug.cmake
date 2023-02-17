#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "spirv-cross-util" for configuration "Debug"
set_property(TARGET spirv-cross-util APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(spirv-cross-util PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "spirv-cross-core"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/spirv-cross-utild.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS spirv-cross-util )
list(APPEND _IMPORT_CHECK_FILES_FOR_spirv-cross-util "${_IMPORT_PREFIX}/lib/spirv-cross-utild.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)