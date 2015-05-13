//
//  CMenuTest.cpp
//  MenuTest
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CMenuTest.hpp"
#include "CPong.hpp"
#include "CFrontEnd.hpp"

CMenuTest * CMenuTest::Get()
{
    return static_cast<CMenuTest *>(CGame::Get());
}

CMenuTest::CMenuTest() : CGame("MenuTest")
{
    mClearColour = CColour::White;
}

void CMenuTest::InitialiseOptions()
{
    GameOptions::viewHeight = 720;
    GameOptions::viewWidth = 1280;
}

void CMenuTest::GoToLocation(int theLocation, std::string filename)
{
    // Set up the next location
    switch (theLocation)
    {
        case kGameLocationPong:
            DEBUG_LOG("Pong requested");
            mNextLocation = new CPong();
            break;
            
        case kGameLocationFrontEnd:
            DEBUG_LOG("Front end requested");
            mNextLocation = new CFrontEnd();
            break;
            
        default:
            DEBUG_LOG("Unimplemented game location - going to dummy location");
            mNextLocation = new CDummyGameLocation();
            break;
    }
}