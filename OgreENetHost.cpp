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

#include "OgreENet.h"

namespace OgreENet
{

OgreENetHost::OgreENetHost(const OgreENetAddress &address, size_t maxClients, size_t maxChannels, enet_uint32 incomingBandwidth, enet_uint32 outgoingBandwidth)
    : _host(enet_host_create(&address.enet_addr(), maxClients, maxChannels, incomingBandwidth, outgoingBandwidth))
{
    if (!_host) {
        Ogre::String strErr = "****** OgreENetException ****** An error occurred while trying to create an ENet server host";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_HOST_NOT_CREATED, strErr, __func__, __FILE__, __LINE__);
    }
}

OgreENetHost::OgreENetHost(size_t maxClients, size_t maxChannels, enet_uint32 incomingBandwidth, enet_uint32 outgoingBandwidth)
    : _host(enet_host_create(NULL, maxClients, maxChannels, incomingBandwidth, outgoingBandwidth))
{
    if (!_host) {
        Ogre::String strErr = "****** OgreENetException ****** An error occurred while trying to create an ENet client host";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_HOST_NOT_CREATED, strErr, __func__, __FILE__, __LINE__);
    }
}

OgreENetHost::~OgreENetHost()
{
    enet_host_destroy(_host);
}

int OgreENetHost::service(OgreENetEvent &event, enet_uint32 timeout)
{
    int ret = enet_host_service(_host, &event.enet_event(), timeout);
    handleEvent(event);
    return ret;
}

OgreENetPeer OgreENetHost::connect(const OgreENetAddress &address, size_t channelCount, enet_uint32 userData)
{
    ENetPeer* peer = enet_host_connect(_host, &address.enet_addr(), channelCount, userData);
    if (!peer) {
        Ogre::String strErr = "****** OgreENetException ****** An error occurred while trying to create a connection";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_NOT_CONN, strErr, __func__, __FILE__, __LINE__);
    }

    return OgreENetPeer(peer);
}

void OgreENetHost::handleEvent(OgreENetEvent &event)
{
    switch(event.type()) {
    case ENET_EVENT_TYPE_CONNECT:
        // Remember the new peer.
        peers.push_back(event.peer().enet_peer());
        break;
    case ENET_EVENT_TYPE_DISCONNECT:
        // This is where you are informed about disconnects.
        // Simply remove the peer from the list of all peers.
        peers.erase(std::find(peers.begin(), peers.end(), event.peer().enet_peer()));
        break;
    default:
        break;
    }
}

void OgreENetHost::capture(OgreENetEvent &event, enet_uint32 timeout)
{
    while(service(event, timeout) > 0) {
        switch(event.type()) {
        case ENET_EVENT_TYPE_CONNECT:
            _injectConnect(event);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            _injectDisconnect(event);
            break;
        default:
            break;
        }
    }
}

}
