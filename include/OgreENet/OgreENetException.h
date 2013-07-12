/*
    This file is part of OgreENet.
    OgreENet is a ENet wrapper for Ogre3d
    Copyright (C) 2013  Sandy Carter

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA, or go to
    http://www.gnu.org/copyleft/lesser.txt.
*/

#ifndef OGREENETEXCEPTION_H
#define OGREENETEXCEPTION_H

#include "OgreENet.h"

namespace OgreENet {

enum OGREENET_EXCEPTION_CODE
{
    OGREENET_ERR_ENET = 1000,
    OGREENET_ERR_BAD_ADDRESS,
    OGREENET_ERR_WAIT,
    OGREENET_ERR_FAIL,
    OGREENET_ERR_INVALID_HANDLE,
    OGREENET_ERR_SHUTDOWN,
    OGREENET_ERR_TIMEOUT,
    OGREENET_ERR_HOST_NOT_CREATED,
    OGREENET_ERR_ALREADY_INIT,
    OGREENET_ERR_ALREADY_CONN,
    OGREENET_ERR_CLEANUP,
    OGREENET_ERR_NO_REMOTE_CONN,
    OGREENET_ERR_NOT_CONN,
    OGREENET_ERR_NOT_INIT,
    OGREENET_ERR_ADDRESS_EXISTS,
    OGREENET_ERR_BAD_SOCK_TYPE
};

class OgreENetException : public Ogre::Exception
{
public:
    OgreENetException(int number, const Ogre::String &description, const Ogre::String &source, const char *file, long line)
        : Ogre::Exception(number, description, source, "OgreENetException", file, line)
    {
    }

};
}

#endif // OGREENETEXCEPTION_H
