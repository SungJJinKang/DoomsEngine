#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "spirv-cross-c" for configuration "RelWithDebInfo"
set_property(TARGET spirv-cross-c APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(spirv-cross-c PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "spirv-cross-glsl;spirv-cross-hlsl;spirv-cross-msl;spirv-cross-cpp;spirv-cross-reflect"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/spirv-cross-c.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS spirv-cross-c )
list(APPEND _IMPORT_CHECK_FILES_FOR_spirv-cross-c "${_IMPORT_PREFIX}/lib/spirv-cross-c.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
