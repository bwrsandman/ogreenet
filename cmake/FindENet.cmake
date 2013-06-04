# - Find ENet
# Find the native ENet includes and library
#
#   ENET_FOUND       - True if ENet found.
#   ENET_INCLUDE_DIR - where to find includes
#   ENET_LIBRARIES   - List of libraries when using ENet.
#

IF (ENET_INCLUDE_DIR)
    # Already in cache, be silent
    SET( ENet_FIND_QUIETLY TRUE )
ENDIF( ENET_INCLUDE_DIR )

FIND_PATH( ENET_INCLUDE_DIR "enet.h"
           PATH_SUFFIXES "enet" )

FIND_LIBRARY( ENET_LIB "enet")

SET(ENET_LIBRARY enet)

# handle the QUIETLY and REQUIRED arguments and set ENET to TRUE if
# all listed variables are TRUE
INCLUDE( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( "ENet" DEFAULT_MSG ENET_INCLUDE_DIR ENET_LIBRARY )

MARK_AS_ADVANCED ( ENET_INCLUDE_DIR ENET_LIBRARY )

