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

#ifndef OGREENETHOST_H
#define OGREENETHOST_H

#include "OgreENet.h"

namespace OgreENet {
class OgreENetHost
{
    friend class OgreENetManager;

    ENetHost* _host;

    OgreENetHost(const OgreENetAddress& address, size_t maxClients, size_t maxChannels, enet_uint32 incomingBandwidth, enet_uint32 outgoingBandwidth);
    ~OgreENetHost();
};
}

#endif // OGREENETHOST_H