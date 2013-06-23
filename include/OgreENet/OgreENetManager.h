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

#ifndef OGREENETMANAGER_H
#define OGREENETMANAGER_H

#include "OgreENet.h"

namespace OgreENet
{

//!  OgreENetManager class.
/*!
    The OgreENetManager is responsible for creating and deleting Sockets.
    You will never create and delete Sockets directly using 'new' and 'delete'.
    The OgreENetManager class follows the singleton pattern.
*/
class OgreENetManager : public Ogre::Singleton<OgreENetManager>
{
public:
    /** Override standard Singleton retrieval.
    @remarks
    Why do we do this? Well, it's because the Singleton
    implementation is in a .h file, which means it gets compiled
    into anybody who includes it. This is needed for the
    Singleton template to work, but we actually only want it
    compiled into the implementation of the class based on the
    Singleton, not all of them. If we don't change this, we get
    link errors when trying to use the Singleton-based class from
    an outside dll.
    @par
    This method just delegates to the template version anyway,
    but the implementation stays in this single compilation unit,
    preventing link errors.
    */
    static OgreENetManager& getSingleton(void);
    /** Override standard Singleton retrieval.
    @remarks
    Why do we do this? Well, it's because the Singleton
    implementation is in a .h file, which means it gets compiled
    into anybody who includes it. This is needed for the
    Singleton template to work, but we actually only want it
    compiled into the implementation of the class based on the
    Singleton, not all of them. If we don't change this, we get
    link errors when trying to use the Singleton-based class from
    an outside dll.
    @par
    This method just delegates to the template version anyway,
    but the implementation stays in this single compilation unit,
    preventing link errors.
    */
    static OgreENetManager* getSingletonPtr(void);

    void initialize();
    void deinitialize();

    OgreENetAddress *createAddress(enet_uint32 host, enet_uint16 port);
    OgreENetAddress *createAddress(const Ogre::String& hostName, enet_uint16 port);

    OgreENetEvent *createEvent();

    OgreENetHost *createServerHost(const OgreENetAddress& address, int maxClients, int maxChannels = 0, int incomingBandwidth = 0, int outgoingBandwidth = 0);
    OgreENetHost *createClientHost(int maxClients, int maxChannels = 0, int incomingBandwidth = 0, int outgoingBandwidth = 0);

    inline OgreENetPacket createPacket(const void* data, size_t dataLength, enet_uint32 flags=ENET_PACKET_FLAG_RELIABLE) { return OgreENetPacket(data, dataLength, flags); }
    template <typename T> inline OgreENetPacket createTypedPacket(const T& data, enet_uint32 flags=ENET_PACKET_FLAG_RELIABLE) { return OgreENetPacket(&data, sizeof(T), flags); }

    ~OgreENetManager();

private:
    OgreENetManager();

    bool mCleanup;
    bool mInitialized;
    std::list<OgreENetHost *> mHostList;
    std::list<OgreENetEvent *> mEventList;
    std::list<OgreENetAddress *> mAddressList;
};
}

#endif // OGREENETMANAGER_H
