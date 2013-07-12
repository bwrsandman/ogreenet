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

#ifndef OGREENETPACKET_H
#define OGREENETPACKET_H

#include "OgreENet.h"

namespace OgreENet
{

class OgreENetPacket
{
    friend class OgreENetManager;
    friend class OgreENetEvent;
    friend class OgreENetPeer;
    friend class OgreENetHost;

    ENetPacket* _packet;

    OgreENetPacket(ENetPacket* packet)
        : _packet(packet)
    {
        if (!_packet) {
            Ogre::String strErr = "****** OgreENetException ****** An error occurred while trying to create an ENet packet";
            Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

            throw OgreENetException(OGREENET_ERR_PACKET_NOT_CREATED, strErr, __func__, __FILE__, __LINE__);
        }
    }

    OgreENetPacket(const void* data, size_t dataLength, enet_uint32 flags)
        : OgreENetPacket(enet_packet_create(data, dataLength, flags))
    {
    }

public:
    inline void destroy() { enet_packet_destroy(_packet); }
    inline size_t dataLength() const { return _packet->dataLength; }
    inline const enet_uint8* data() const { return _packet->data; }
    template <typename T> inline T& typedData() const { return *((T*)_packet->data); }
    inline int resize(size_t dataLength) { return enet_packet_resize(_packet, dataLength); }

};

}

#endif // OGREENETPACKET_H

