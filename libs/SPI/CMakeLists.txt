cmake_minimum_required(VERSION 3.5)
project(SPI VERSION 1.0.0 LANGUAGES CXX)

add_library(SPI
        SPI.cpp)

add_library(RovCommon::SPI ALIAS SPI)

target_link_libraries(SPI RovCommon::Controller)

target_include_directories(SPI
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(SPI PRIVATE cxx_auto_type)
target_compile_options(SPI PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
install(TARGETS SPI
        EXPORT RovCommonTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
