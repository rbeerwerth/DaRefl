
set(MVVM_DISCOVER_TESTS OFF)
set(MVVM_BUILD_EXAMPLES OFF)
add_subdirectory(qt-mvvm)

if( NOT EXISTS "${CMAKE_SOURCE_DIR}/extern/eigen3/.git" )
    message( FATAL_ERROR "Eigen3 submodule was not initialized. Please run
                          git submodule update --init")
endif()
add_subdirectory(eigen3)
