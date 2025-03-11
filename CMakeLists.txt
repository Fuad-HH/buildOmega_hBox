cmake_minimum_required(VERSION 3.20)
project(buildOmega_hBox LANGUAGES CXX)

include(GNUInstallDirs)

find_package(Omega_h REQUIRED)
find_package(Kokkos QUIET CONFIG)

add_executable(buildOmega_hBox main.cpp)
target_link_libraries(buildOmega_hBox Omega_h::omega_h)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_RPATH "${CMAKE_BUILD_RPATH}:${Omega_h_DIR}/lib:${Omega_h_DIR}/lib64")

if(Kokkos_FOUND AND Kokkos_ROOT)
    set(KOKKOS_LIBRARY_DIR "${Kokkos_ROOT}/lib64")
    if(EXISTS ${KOKKOS_LIBRARY_DIR})
        set(CMAKE_BUILD_RPATH "${CMAKE_BUILD_RPATH}:${KOKKOS_LIBRARY_DIR}")
        set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:${KOKKOS_LIBRARY_DIR}")
        message(STATUS "Added Kokkos library directory to RPATH: ${KOKKOS_LIBRARY_DIR}")
    else()
        message(WARNING "Kokkos library directory not found: ${KOKKOS_LIBRARY_DIR}")
    endif()
else()
    message(WARNING "Kokkos not found or Kokkos_ROOT not set. Kokkos libraries may not be found at runtime if Omega_h used here was built with Kokkos.")
endif()

install(TARGETS buildOmega_hBox
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

set_target_properties(buildOmega_hBox PROPERTIES
        INSTALL_RPATH "${CMAKE_INSTALL_RPATH}"
        INSTALL_RPATH_USE_LINK_PATH TRUE
)