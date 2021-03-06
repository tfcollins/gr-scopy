# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR} ${M2K_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND scopy_sources
    analog_source_impl.cc
    #test2_impl.cc
    )

set(scopy_sources "${scopy_sources}" PARENT_SCOPE)
if(NOT scopy_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT scopy_sources)

add_library(gnuradio-scopy SHARED ${scopy_sources})
target_link_libraries(gnuradio-scopy ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES} ${M2K_LIBRARIES})
set_target_properties(gnuradio-scopy PROPERTIES DEFINE_SYMBOL "gnuradio_scopy_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-scopy PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
# include(GrMiscUtils)
# GR_LIBRARY_FOO(gnuradio-scopy RUNTIME_COMPONENT "scopy_runtime" DEVEL_COMPONENT "scopy_devel")

install(TARGETS gnuradio-scopy
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
# include(GrTest)
#
# include_directories(${CPPUNIT_INCLUDE_DIRS})
#
# list(APPEND test_scopy_sources
#     ${CMAKE_CURRENT_SOURCE_DIR}/
# )
#
# add_executable(test-scopy ${test_scopy_sources})
#
# target_link_libraries(
#   test-scopy
#   ${GNURADIO_RUNTIME_LIBRARIES}
#   ${Boost_LIBRARIES}
#   ${CPPUNIT_LIBRARIES}
#   ${LIBM2K_LIBRARIES}
#   gnuradio-scopy
# )

# GR_ADD_TEST(test_scopy test-scopy)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")
