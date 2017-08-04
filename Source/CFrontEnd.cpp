//
//  CFrontEnd.cpp
//  MenuTest
//
//  Created by Tim Brier on 08/05/2015.
//
//

#include "CFrontEnd.hpp"
#include "GUIMenu/CButtonWidget.hpp"
#include "CMenuTest.hpp"
#include "CPong.hpp"

CFrontEnd::CFrontEnd() : CGUIMenu()
{
    float width = GameOptions::viewWidth / 2.0f;
    float height = 50.0f;
    
    float xPos = (GameOptions::viewWidth - width) / 2.0f;
    float yPos = 200.0f;
    float yOffset = 70.0f;
    
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Play", std::bind(&CFrontEnd::HandlePlayButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Options", std::bind(&CFrontEnd::HandleOptionsButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Exit", std::bind(&CFrontEnd::HandleExitButton, this)));
    yPos += yOffset;
    
}

CFrontEnd::~CFrontEnd()
{
    
}

void CFrontEnd::HandlePlayButton()
{
    DEBUG_LOG("Play button pressed");
    CMenuTest::Get()->PushGameLocation(new CPong());
}

void CFrontEnd::HandleOptionsButton()
{
    DEBUG_LOG("Options button pressed");
}

void CFrontEnd::HandleExitButton()
{
    DEBUG_LOG("Exit button pressed");
    CMenuTest::Get()->ExitGame();
}
