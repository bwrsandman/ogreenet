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

#ifndef OGREENETEVENT_H
#define OGREENETEVENT_H

#include "OgreENet.h"

namespace OgreENet {
class OgreENetEvent
{
    friend class OgreENetManager;

    ENetEvent _event;

    OgreENetEvent() {}

public:
    inline OgreENetPacket packet() const { return _event.packet; }
    inline OgreENetPeer peer() const { return OgreENetPeer(_event.peer); }
    inline ENetEventType type() const { return _event.type; }
    inline enet_uint8 channelID() const { return _event.channelID; }
    inline enet_uint32 data() const { return _event.data; }

    inline ENetEvent& enet_event() { return _event; }
};

}

#endif // OGREENETEVENT_H
