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

#ifndef OGREENETADDRESS_H
#define OGREENETADDRESS_H

#include "OgreENet.h"

namespace OgreENet {
class OgreENetAddress
{
    friend class OgreENetManager;
    friend class OgreENetPeer;

    ENetAddress _address;

    OgreENetAddress(const ENetAddress& address) : _address(address) {}
    OgreENetAddress(enet_uint32 host, enet_uint16 port) { setHost(host); setPort(port); }
    OgreENetAddress(const Ogre::String& hostName, enet_uint16 port) { setHost(hostName); setPort(port); }

    inline void setHost(const Ogre::String& hostName) { enet_address_set_host(&_address, hostName.c_str()); }
    inline void setHost(enet_uint32 host) { _address.host = host; }

    inline void setPort(int port) { _address.port = port; }

public:
    inline const ENetAddress& enet_addr() const { return _address; }
    inline enet_uint32 host() const { return _address.host; }
    inline enet_uint16 port() const { _address.port; }
};
}

#endif // OGREENETADDRESS_H
