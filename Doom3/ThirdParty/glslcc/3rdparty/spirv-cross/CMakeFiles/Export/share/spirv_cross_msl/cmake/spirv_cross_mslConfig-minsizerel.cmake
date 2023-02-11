#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "spirv-cross-msl" for configuration "MinSizeRel"
set_property(TARGET spirv-cross-msl APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(spirv-cross-msl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_MINSIZEREL "spirv-cross-glsl"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/spirv-cross-msl.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS spirv-cross-msl )
list(APPEND _IMPORT_CHECK_FILES_FOR_spirv-cross-msl "${_IMPORT_PREFIX}/lib/spirv-cross-msl.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
