CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

PROJECT(librarytwo
  DESCRIPTION "A second sample project"
  VERSION 0.0.1
  # include C so that we can link against C libraries (e.g., MPI::MPI_C) easily
  LANGUAGES CXX)

OPTION(BUILD_SHARED_LIBS "Whether or not to build shared libraries." ON)

# Start building up RPATH:
SET(CMAKE_BUILD_RPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

SET(LIBRARYONE_INCLUDE_DIRS ${LIBRARYONE_ROOT}/include/)
FIND_LIBRARY(LIBRARYONE_LIBRARIES NAMES helloint HINTS ${LIBRARYONE_ROOT}/lib /usr/lib)

IF("${LIBRARYONE_LIBRARIES}" STREQUAL "LIBRARYONE_LIBRARIES-NOTFOUND")
  MESSAGE(FATAL_ERROR "Unable to find libraryone!")
ENDIF()

SET(ALL_SRC source/two.cc)

ADD_LIBRARY(librarytwo ${ALL_SRC})
TARGET_LINK_LIBRARIES(librarytwo PUBLIC ${LIBRARYONE_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(librarytwo PUBLIC ${LIBRARYONE_INCLUDE_DIRS})

INSTALL(TARGETS librarytwo COMPONENT library)
