//
//  CFrontEnd.cpp
//  MenuTest
//
//  Created by Tim Brier on 08/05/2015.
//
//

#include "CFrontEnd.hpp"

CFrontEnd::CFrontEnd() : CGUIMenu()
{
    float width = GameOptions::viewWidth / 2.0f;
    float height = 50.0f;
    
    float xPos = (GameOptions::viewWidth - width) / 2.0f;
    float yPos = 200.0f;
    float yOffset = 70.0f;
    
    AddWidget(CWidget(xPos, yPos, width, height, "Play"));
    yPos += yOffset;
    AddWidget(CWidget(xPos, yPos, width, height, "Options"));
    yPos += yOffset;
    AddWidget(CWidget(xPos, yPos, width, height, "Exit"));
    yPos += yOffset;
    
}

CFrontEnd::~CFrontEnd()
{
    
}