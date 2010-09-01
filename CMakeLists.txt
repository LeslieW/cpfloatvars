cmake_minimum_required (VERSION 2.6)

project (CPFloatVars)

##########################################################################
# Version information                                                    #
##########################################################################
set(CPFLOATVARS_VERSION_MAJOR 1)
set(CPFLOATVARS_VERSION_MINOR 0)
set(CPFLOATVARS_VERSION "${CPFLOATVARS_VERSION_MAJOR}.${CPFLOATVARS_VERSION_MINOR}")
##########################################################################

##########################################################################
## user configurable options
##########################################################################
option(BUILD_SHARED_LIB "Build as a shared library" ON)
option(BUILD_STATIC_LIB "Build as a shared library" OFF)
option(BUILD_EXAMPLES "Build the examples" ON)

##########################################################################
## C compiler definitions
##########################################################################
ADD_DEFINITIONS( "-DGECODE_HAS_FLOAT_VARS" )
# This *must* match the visibility used when building gecode
#if(GCC_VISIBILITY)
#	ADD_DEFINITIONS("-fvisibility=default")
#	ADD_DEFINITIONS("-DGECODE_GCC_HAS_CLASS_VISIBILITY")
#endif()

##########################################################################
## Boost libraries
##########################################################################
#set(REQ_BOOST_LIBS graph)
#if(BUILD_TEST)
#  list(APPEND REQ_BOOST_LIBS unit_test_framework)
#endif(BUILD_TEST)

##########################################################################
## Find Boost
##########################################################################
#set(Boost_USE_STATIC_LIBS ON)
#find_package(Boost 1.42.0 COMPONENTS ${REQ_BOOST_LIBS})
#message(STATUS "Boost include path: ${Boost_INCLUDE_DIR}")
#message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
#include_directories("${Boost_INCLUDE_DIR}")

##########################################################################
## Find Gecode
##########################################################################
if (UNIX)
  set(GECODE_KERNEL)
  find_library(GECODE_KERNEL gecodekernel)
  message(STATUS "Gecode kernel: ${GECODE_KERNEL}")

  set(GECODE_SUPPORT)
  find_library(GECODE_SUPPORT gecodesupport)
  message(STATUS "Gecode support: ${GECODE_SUPPORT}")

  set(GECODE_INT)
  find_library(GECODE_INT gecodeint)
  message(STATUS "Gecode int: ${GECODE_INT}")

  set(GECODE_SET)
  find_library(GECODE_SET gecodeset)
  message(STATUS "Gecode set: ${GECODE_SET}")

  set(GECODE_SEARCH)
  find_library(GECODE_SEARCH gecodesearch)
  message(STATUS "Gecode search: ${GECODE_SEARCH}")

  set(GECODE_MINIMODEL)
  find_library(GECODE_MINIMODEL gecodeminimodel)
  message(STATUS "Gecode minimodel: ${GECODE_MINIMODEL}")

  set(GECODE_LIBRARY ${GECODE_KERNEL} ${GECODE_SUPPORT} ${GECODE_INT}
    ${GECODE_SET} ${GECODE_SEARCH} ${GECODE_MINIMODEL})

  set(GECODE_GIST)
  find_library(GECODE_GIST gecodegist)
  message(STATUS "Gecode gist: ${GECODE_GIST}")

  if (GECODE_GIST)
    list(APPEND GECODE_LIBRARY ${GECODE_GIST})
  endif (GECODE_GIST)

  find_path(GECODE_INCLUDES gecode/kernel.hh)
  include_directories("${GECODE_INCLUDES}")

  #message(STATUS "Gecode library: ${GECODE_LIBRARY}")
elseif (WIN32)
  message(FATAL_ERROR "This architecture is not yet supported")
else (UNIX AND (NOT GECODE_AS_FRAMEWORK))
  if (NOT GECODE_AS_FRAMEWORK)
    message(FATAL_ERROR "Unknown architecture")
  endif (NOT GECODE_AS_FRAMEWORK)
endif (UNIX)

##########################################################################
## Building options
##########################################################################
if (BUILD_SHARED_LIB)
   set(GRAPH_LIBRARY_TYPE SHARED)
else (BUILD_SHARED_LIB)
   set(GRAPH_LIBRARY_TYPE STATIC)
endif (BUILD_SHARED_LIB)

##########################################################################
# Main library                                                           #
##########################################################################
add_subdirectory(gecode/float)

##########################################################################
# Examples                                                               #
##########################################################################
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)

##########################################################################
# Uninstall
##########################################################################
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

