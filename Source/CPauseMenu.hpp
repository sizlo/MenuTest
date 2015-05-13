//
//  CPauseMenu.hpp
//  MenuTest
//
//  Created by Tim Brier on 13/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __MenuTest__CPauseMenu__
#define __MenuTest__CPauseMenu__

#include "GUIMenu/CGUIMenu.hpp"
#include "CPong.hpp"

class CPauseMenu : public CGUIMenu
{
public:
    CPauseMenu(CPong *parent);
    ~CPauseMenu();
private:
    void HandleResumeButton();
    void HandleRestartButton();
    void HandleExitButton();
    void HandleExitGameButton();

    CPong *mParentGame;
};

#endif /* defined(__MenuTest__CPauseMenu__) */