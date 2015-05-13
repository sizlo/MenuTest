//
//  CFrontEnd.hpp
//  MenuTest
//
//  Created by Tim Brier on 08/05/2015.
//
//

#ifndef __MenuTest__CFrontEnd__
#define __MenuTest__CFrontEnd__

#include "GUIMenu/CGUIMenu.hpp"

class CFrontEnd : public CGUIMenu
{
public:
    CFrontEnd();
    ~CFrontEnd();
private:
    void HandlePlayButton();
    void HandleOptionsButton();
    void HandleExitButton();
};

#endif /* defined(__MenuTest__CFrontEnd__) */
