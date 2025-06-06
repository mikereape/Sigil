########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 3.18 ) 

project( sigilgumbo C )

set( GUMBO_LIBRARIES ${PROJECT_NAME} CACHE INTERNAL "" )
set( GUMBO_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "" )

file( GLOB SOURCES *.c )
list( SORT SOURCES )

if( APPLE )
        set(CMAKE_MACOSX_RPATH 1)
endif()

if ( MSVC )
     set( SOURCES ${SOURCES} include/gumbo_windll.def)
endif()

add_library( sigilgumbo SHARED ${SOURCES} ) 

# Special compiler and linker flags for MSVC
if( MSVC )
    set ( EXTRA_INC include/ )
    include_directories( SYSTEM ${EXTRA_INC} )
    add_definitions( -Dinline=__inline )

    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
    set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Oi /GL" )
    set( CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS} /LTCG" )
endif()

if( UNIX AND NOT APPLE )
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99" )
endif()
