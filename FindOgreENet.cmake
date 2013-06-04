# - Find OgreENet
# Find the native OgreENet includes and library
#
#   OGREENET_FOUND       - True if OgreENet found.
#   OGREENET_INCLUDE_DIR - where to find includes
#   OGREENET_LIBRARIES   - List of libraries when using OgreENet.
#

IF (OGREENET_INCLUDE_DIR)
    # Already in cache, be silent
    SET( OgreENet_FIND_QUIETLY TRUE )
ENDIF( OGREENET_INCLUDE_DIR )

FIND_PATH( OGREENET_INCLUDE_DIR "OgreENet.h"
           PATH_SUFFIXES "OgreENet" )

FIND_LIBRARY( OGREENET_LIB "OgreENet")

SET(OGREENET_INCLUDE_DIR "${OGREENET_INCLUDE_DIR}")
SET(OGREENET_LIBRARIY OgreENet)

# handle the QUIETLY and REQUIRED arguments and set OGREENET_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( "OgreENet" DEFAULT_MSG OGREENET_INCLUDE_DIR OGREENET_LIBRARY )

MARK_AS_ADVANCED ( OGREENET_INCLUDE_DIR OGREENET_LIBRARIES )

