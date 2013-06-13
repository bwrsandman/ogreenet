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
    std::list<ENetPeer *> peers;

    OgreENetHost(const OgreENetAddress& address, size_t maxClients, size_t maxChannels, enet_uint32 incomingBandwidth, enet_uint32 outgoingBandwidth);
    OgreENetHost(size_t maxClients, size_t maxChannels, enet_uint32 incomingBandwidth, enet_uint32 outgoingBandwidth);

    ~OgreENetHost();

public:
    int service(OgreENetEvent& event, enet_uint32 timeout = 0);
    OgreENetPeer connect(const OgreENetAddress& address, size_t channelCount, enet_uint32 userData);

    /**
    @remarks
        Register/unregister a ENet Listener - Only one allowed for simplicity.
    @param listener
        Send a pointer to a class derived from OgreENetListener or 0 to clear
        the callback
    */
    virtual void setEventCallback(OgreENetListener *listener) { mListener = listener;}

protected:
    void handleEvent(OgreENetEvent& event);
    OgreENetListener *mListener;

private:
    inline void _injectConnect(OgreENetEvent &event) { if (mListener) mListener->hostConnected(event); }
    inline void _injectDisconnect(OgreENetEvent &event) { if (mListener) mListener->hostDisconnected(event); }
    inline void _injectReceive(OgreENetEvent &event) { if (mListener) mListener->hostReceived(event); }
};

}

#endif // OGREENETHOST_H
