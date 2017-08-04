//
//  Main.cpp
//  MenuTest
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CMenuTest.hpp"
#include "CFrontEnd.hpp"

int main(int argc, char **argv)
{
    CMenuTest theGame;
    theGame.Init(new CFrontEnd());
    int returnCode = theGame.Run();
    theGame.Cleanup();
    
    return returnCode;
}
