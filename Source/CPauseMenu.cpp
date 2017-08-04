//
//  CPauseMenu.cpp
//  MenuTest
//
//  Created by Tim Brier on 13/05/2015.
//
//

#include "CPauseMenu.hpp"
#include "GUIMenu/CButtonWidget.hpp"
#include "CMenuTest.hpp"
#include "CFrontEnd.hpp"

CPauseMenu::CPauseMenu(CPong *parent) : CGUIMenu()
{
    mParentGame = parent;

    float width = GameOptions::viewWidth / 2.0f;
    float height = 50.0f;
    
    float xPos = (GameOptions::viewWidth - width) / 2.0f;
    float yPos = 200.0f;
    float yOffset = 70.0f;
    
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Resume", std::bind(&CPauseMenu::HandleResumeButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Restart", std::bind(&CPauseMenu::HandleRestartButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Exit to Menu", std::bind(&CPauseMenu::HandleExitButton, this)));
    yPos += yOffset;
    AddWidget(new CButtonWidget(xPos, yPos, width, height, "Exit to Desktop", std::bind(&CPauseMenu::HandleExitGameButton, this)));
    yPos += yOffset;
}

CPauseMenu::~CPauseMenu()
{
    
}

void CPauseMenu::HandleResumeButton()
{
    mParentGame->UnpauseGame();
}

void CPauseMenu::HandleRestartButton()
{
    mParentGame->InitialiseBallVel();
    mParentGame->UnpauseGame();
}

void CPauseMenu::HandleExitButton()
{
    mParentGame->UnpauseGame();
    CMenuTest::Get()->PopGameLocation();
}

void CPauseMenu::HandleExitGameButton()
{
    CMenuTest::Get()->ExitGame();
}
