cmake_minimum_required(VERSION 3.5)
project(RovCommon)

include_directories(include)

# Add here all libraries' directories
#add_subdirectory(name_of_directory)
add_subdirectory(libs/Controller)

# Install and export (do not touch this part)
install(
  EXPORT RovCommonTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/RovCommon
  NAMESPACE RovCommon::
  FILE RovCommonTargets.cmake
  )

include(CMakePackageConfigHelpers)
configure_package_config_file( 
  "Config.cmake.in" 
  "RovCommonConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/RovCommon
  PATH_VARS
    CMAKE_INSTALL_LIBDIR
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/RovCommonConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )

### Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/RovCommonConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/RovCommonConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/RovCommon"
  )
