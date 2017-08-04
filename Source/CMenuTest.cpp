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
