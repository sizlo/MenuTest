//
//  CPong.hpp
//  MenuTest
//
//  Created by Tim Brier on 08/05/2015.
//
//

#ifndef __MenuTest__CPong__
#define __MenuTest__CPong__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CGameLocation.hpp"
#include "CMessageListener.hpp"

class CPauseMenu;

class CPong :   public CUpdateable,
                public CRenderable,
                public CGameLocation,
                public CMessageListener<CEvent>
{
public:
    CPong();
    ~CPong();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void Enter();
    void Exit();
    
    bool HandleMessage(CEvent e);

    void InitialiseBallVel();

    void PauseGame();
    void UnpauseGame();
    
private:   
    CConvexShape mPlayer1;
    CConvexShape mPlayer2;
    CConvexShape mBall;
    
    float mPlayer1Speed;
    float mPlayer2Speed;
    float mBallSpeed;
    
    CVector2f mBallVelocity;

    bool mPaused;
    CPauseMenu *mPauseMenu;
};

#endif /* defined(__MenuTest__CPong__) */
