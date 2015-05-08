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
    // If we're already in a location leave it
    if (mCurrentLocation != NULL)
    {
        mCurrentLocation->Exit();
        SAFE_DELETE(mCurrentLocation);
    }
    
    switch (theLocation)
    {
        case kGameLocationPong:
            DEBUG_LOG("Pong requested");
            mCurrentLocation = new CPong();
            break;
            
        case kGameLocationFrontEnd:
            DEBUG_LOG("Front end requested");
            mCurrentLocation = new CFrontEnd();
            break;
            
        default:
            DEBUG_LOG("Unimplemented game location - going to dummy location");
            mCurrentLocation = new CDummyGameLocation();
            break;
    }
    
    mCurrentLocation->Enter();
}