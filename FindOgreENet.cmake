# - Find OgreENet
# Find the native OgreENet includes and library
#
#   OGREENET_FOUND       - True if OgreENet found.
#   OGREENET_INCLUDE_DIR - where to find includes
#   OGREENET_LIBRARIES   - List of libraries when using OgreENet.
#
# Copyright (c) 2013, Sandy Carter
#
# Redistribution and use is allowed according the license terms
# of OgreENet, which this file is integrated part of.

# Find OgreENet.h and the corresponding library (libOgreENet.a)
FIND_PATH( OgreENet_INCLUDE_DIR OgreENet.h )
FIND_LIBRARY( OgreENet_LIBRARIES NAMES OgreENet)

# Handle the QUIETLY and REQUIRED arguments and set OGREENET_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( OgreENet DEFAULT_MSG OgreENet_INCLUDE_DIR OgreENet_LIBRARIES )
