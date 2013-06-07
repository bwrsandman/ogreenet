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

#ifndef OGREENETLISTENER_H
#define OGREENETLISTENER_H

#include "OgreENet.h"

namespace OgreENet {

/**
    To recieve buffered enet events, derive a class from this, and implement the
    methods here. Then set the call back to your Host instance with
    OgreENetHost::setEventCallback
*/
class OgreENetListener
{
public:
    virtual ~OgreENetListener() {}
    virtual bool hostConnected(const OgreENetEvent &event) = 0;
    virtual bool hostReceived(const OgreENetEvent &event) = 0;
    virtual bool hostDisconnected(const OgreENetEvent &event) = 0;
};

}

#endif // OGREENETLISTENER_H
