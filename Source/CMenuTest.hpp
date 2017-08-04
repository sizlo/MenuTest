//
//  CMenuTest.hpp
//  MenuTest
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __MenuTest__CMenuTest__
#define __MenuTest__CMenuTest__

#include "CGame.hpp"

class CMenuTest : public CGame
{
public:
    static CMenuTest * Get();
    
    CMenuTest();
    
    void InitialiseOptions();
    void GoToLocation(int theLocation, std::string filename = std::string());
};

#endif /* defined(__MenuTest__CMenuTest__) */
