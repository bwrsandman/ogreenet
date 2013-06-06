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

template<> OgreENetManager* Ogre::Singleton<OgreENetManager>::msSingleton = 0;

/*
 * OgreENetManager - Constructor
 * private so won't get documented
 */
OgreENetManager::OgreENetManager():
    mInitialized(false),
    mCleanup(false)
{
    Ogre::LogManager::getSingleton().logMessage("Creating the OgreENetManager");

    //make sure we start with empty host and socket list
    mHostList.empty();
    mAddressList.empty();
}

OgreENetManager* OgreENetManager::getSingletonPtr(void)
{
    if(!msSingleton)
    {
        msSingleton = new OgreENetManager();
    }
    return Ogre::Singleton<OgreENetManager>::getSingletonPtr();
}

OgreENetManager& OgreENetManager::getSingleton(void)
{
    if(!msSingleton)
    {
        msSingleton = new OgreENetManager();
    }
    return Ogre::Singleton<OgreENetManager>::getSingleton();
}


/*!
    @param[in]  none
    @param[out] none

    @exception  OGREENET_ERR_ALREADY_INIT   if the OgreENetManager has already been initialized
    @exception  OGREENET_ERR_CLEANUP        if the OgreENetManager is in the process of being cleaned-up
    @exception  OGREENET_ERR_ENET           if ENet fails for some reason

    @remarks
    Because the OgreENetManager constructor is static, so its body is kept as
    minimal as possible.
    However, the OgreENetManager is responsible for starting ENet, and that is
    the purpose of the OgreENetManager::Initialize function. This function must
    be called before any other OgreENet functions are called. Conversely, the
    OgreENetManager::Cleanup function must be called when the OgreENet
    application ends.
*/
void OgreENetManager::initialize()
{
    Ogre::LogManager::getSingleton().logMessage("Starting the OgreENetManager");

    if(mInitialized)
    {
        Ogre::String strErr = "****** OgreENetException ****** Cannot start OgreENetManager because it has already been started";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_ALREADY_INIT, strErr, "OgreENetManager::Initialize", __FILE__, __LINE__);
    }

    if(mCleanup)
    {
        Ogre::String strErr = "****** OgreENetException ****** Cannot clean-up the OgreENetManager because it is already in the process of being cleaned-up";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_CLEANUP, strErr, "OgreENetManager::CleanUp", __FILE__, __LINE__);
    }

    // Init ENet
    if (enet_initialize() != 0)
    {
        Ogre::String strErr = "****** OgreENetException ****** ENet failed to initialize.";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);
        throw OgreENetException(OGREENET_ERR_ENET, strErr, "OgreENetManager::Initialize", __FILE__, __LINE__);
    }

    mInitialized = true;

    Ogre::LogManager::getSingleton().logMessage("OgreENetManager started OK");
}

/*!
    @param[in]  none
    @param[out] none

    @exception  OGREENET_ERR_NOT_INIT       if the OgreENetManager has not yet been initialized
    @exception  OGREENET_ERR_CLEANUP        if the OgreENetManager is already in the process of being cleaned-up

    @remarks
    Because the OgreENetManager destructor is static, so its body is kept as
    minimal as possible.
    However, the OgreENetManager is responsible for releasing resources within
    ENet, and that is the purpose of the OgreENetManager::Deinitialize function.
    This function must be called when the OgreENet application ends. After this
    function has been called, no other OgreENet functions can be called until
    OgreENetManager::Initialize has been called again.
*/
void OgreENetManager::deinitialize()
{
    Ogre::LogManager::getSingleton().logMessage("Performing clean-up on the OgreENetManager");

    if(!mInitialized) {
        Ogre::String strErr = "****** OgreENetException ****** Cannot clean-up the OgreENetManager because it has not yet been started";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        //calling this function would create an instance of the socket manager - delete it
        delete(this);
        msSingleton = NULL;

        throw OgreENetException(OGREENET_ERR_NOT_INIT, strErr, "OgreENetManager::CleanUp", __FILE__, __LINE__);
    }

    if(mCleanup) {
        Ogre::String strErr = "****** OgreENetException ****** Cannot clean-up the OgreENetManager because it is already in the process of being cleaned-up";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_CLEANUP, strErr, "OgreENetManager::CleanUp", __FILE__, __LINE__);
    }

    // Make sure the user can't delete hosts whilst we are cleaning up (the
    // socket manager still can though because it uses a different function -
    // the private one)
    mCleanup = true;

    Ogre::String strText = "Deleting " + Ogre::StringConverter::toString(mAddressList.size()) + " addresses";
    Ogre::LogManager::getSingleton().logMessage(strText);
    mAddressList.clear();

    strText = "Deleting " + Ogre::StringConverter::toString(mHostList.size()) + " hosts";
    Ogre::LogManager::getSingleton().logMessage(strText);
    mHostList.clear();

    // Deinitialize enet
    enet_deinitialize();

    Ogre::LogManager::getSingleton().logMessage("OgreENetManager deinitialized");

    // Reset variables
    mCleanup = false;
    mInitialized = false;

    // Finally delete the instance
    delete(this);
    msSingleton = NULL;
}

OgreENetAddress *OgreENetManager::createAddress(enet_uint32 host, enet_uint16 port)
{
    Ogre::String strText = "Preparing to create address, number of created addresses is currently ";
    strText += Ogre::StringConverter::toString(mAddressList.size());
    Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_TRIVIAL, strText);

    if(!mInitialized) {
        Ogre::String strErr = "****** OgreENetException ****** Cannot create address because either the OgreENetManager has not been started, or it has been cleaned up";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_NOT_INIT, strErr, __func__, __FILE__, __LINE__);
    }

    if(mCleanup) {
        Ogre::String strErr = "****** OgreENetException ****** Cannot create address because it is in the process of being cleaned-up";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_CLEANUP, strErr, __func__, __FILE__, __LINE__);
    }

    OgreENetAddress *ret = new OgreENetAddress(host, port);
    mAddressList.push_back(ret);

    strText = "Address created OK, number of created addresses is now ";
    strText += Ogre::StringConverter::toString(mAddressList.size());
    Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_TRIVIAL, strText);

    return ret;
}

OgreENetAddress *OgreENetManager::createAddress(const Ogre::String& hostName, enet_uint16 port)
{
    Ogre::String strText = "Preparing to create address, number of created addresses is currently ";
    strText += Ogre::StringConverter::toString(mAddressList.size());
    Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_TRIVIAL, strText);

    if(!mInitialized) {
        Ogre::String strErr = "****** OgreENetException ****** Cannot create address because either the OgreENetManager has not been started, or it has been cleaned up";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_NOT_INIT, strErr, __func__, __FILE__, __LINE__);
    }

    if(mCleanup) {
        Ogre::String strErr = "****** OgreENetException ****** Cannot create address because it is in the process of being cleaned-up";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_CLEANUP, strErr, __func__, __FILE__, __LINE__);
    }

    OgreENetAddress *ret = new OgreENetAddress(hostName, port);
    mAddressList.push_back(ret);

    strText = "Address created OK, number of created addresses is now ";
    strText += Ogre::StringConverter::toString(mAddressList.size());
    Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_TRIVIAL, strText);

    return ret;
}

OgreENetHost *OgreENetManager::createServerHost(const OgreENetAddress &address, int maxClients, int maxChannels, int incomingBandwidth, int outgoingBandwidth)
{
    Ogre::String strText = "Preparing to create server host, number of created hosts is currently ";
    strText += Ogre::StringConverter::toString(mHostList.size());
    Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_TRIVIAL, strText);

    if(!mInitialized) {
        Ogre::String strErr = "****** OgreENetException ****** Cannot create host because either the OgreENetManager has not been started, or it has been cleaned up";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_NOT_INIT, strErr, __func__, __FILE__, __LINE__);
    }

    if(mCleanup) {
        Ogre::String strErr = "****** OgreENetException ****** Cannot create host because it is in the process of being cleaned-up";
        Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_CRITICAL, strErr);

        throw OgreENetException(OGREENET_ERR_CLEANUP, strErr, __func__, __FILE__, __LINE__);
    }

    OgreENetHost *ret = new OgreENetHost(address, maxClients, maxChannels, incomingBandwidth, outgoingBandwidth);
    mHostList.push_back(ret);

    strText = "Server host created OK, number of created hosts is now ";
    strText += Ogre::StringConverter::toString(mHostList.size());
    Ogre::LogManager::getSingleton().logMessage(Ogre::LogMessageLevel::LML_TRIVIAL, strText);

    return ret;
}

OgreENetManager::~OgreENetManager()
{
    Ogre::LogManager::getSingleton().logMessage("Destroying the OgreENetManager");
}

}
