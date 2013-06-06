cmake_minimum_required(VERSION 2.8)

set(PROJ "OgreENet")

project(${PROJ})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

if(WIN32)
    set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH
        $ENV{OGRE_HOME}/Samples/include
    )
endif(WIN32)
 
if(UNIX)
    if(EXISTS "/usr/local/lib/OGRE/cmake")

      set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
      set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

    elseif(EXISTS "/usr/lib/OGRE/cmake")

      set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
      set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

    else ()
      message(SEND_ERROR "Failed to find module path.")
    endif(EXISTS "/usr/local/lib/OGRE/cmake")
endif(UNIX)

find_package(OGRE REQUIRED)
find_package(ENet REQUIRED)

set(ENet_INCLUDE_DIR include/OgreENet)

include_directories(${OGRE_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/OgreENet)

set(HDRS
    ${ENet_INCLUDE_DIR}/OgreENet.h
    ${ENet_INCLUDE_DIR}/OgreENetManager.h
    ${ENet_INCLUDE_DIR}/OgreENetException.h
    ${ENet_INCLUDE_DIR}/OgreENetHost.h
    ${ENet_INCLUDE_DIR}/OgreENetAddress.h
    ${ENet_INCLUDE_DIR}/OgreENetEvent.h
    ${ENet_INCLUDE_DIR}/OgreENetPeer.h
)
 
set(SRCS
    ./OgreENet.cpp
    ./OgreENetManager.cpp
    ./OgreENetException.cpp
    ./OgreENetHost.cpp
    ./OgreENetAddress.cpp
    ./OgreENetEvent.cpp
    ./OgreENetPeer.cpp
    ${HDRS}
)

add_definitions("-std=c++0x")

add_library(${PROJ} ${SRCS})

set(INCLUDE_INSTALL_DIR include/${PROJ})
target_link_libraries(${PROJ} ${ENET_LIB})

install(TARGETS ${PROJ}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

install(FILES ${HDRS} DESTINATION ${INCLUDE_INSTALL_DIR})

install(FILES FindOgreENet.cmake DESTINATION lib/${PROJ}/cmake)

