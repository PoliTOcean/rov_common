cmake_minimum_required(VERSION 3.5)
project(PolitoceanRovCommon)

include_directories(include)

# Add here all libraries' directories
#add_subdirectory(name_of_directory)
add_subdirectory(libs/Controller)

# Install and export (do not touch this part)
install(
  EXPORT PolitoceanRovCommonTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanRovCommon
  NAMESPACE PolitoceanRovCommon::
  FILE PolitoceanRovCommonTargets.cmake
  )

include(CMakePackageConfigHelpers)
configure_package_config_file( 
  "Config.cmake.in" 
  "PolitoceanRovCommonConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanRovCommon
  PATH_VARS
    CMAKE_INSTALL_LIBDIR
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/PolitoceanRovCommonConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )

### Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanRovCommonConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/PolitoceanRovCommonConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/PolitoceanRovCommon"
  )
