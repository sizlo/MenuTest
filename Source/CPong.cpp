//
//  CPong.cpp
//  MenuTest
//
//  Created by Tim Brier on 08/05/2015.
//
//

#include "CPong.hpp"
#include "CMenuTest.hpp"
#include "CMessageBroadcaster.hpp"
#include "GameOptions.hpp"
#include "MathsUtilities.hpp"
#include "CPauseMenu.hpp"

CPong::CPong()
{
    mPaused = false;
    mPauseMenu = new CPauseMenu(this);

    mPlayer1 = CConvexShape(4);
    mPlayer1.setPoint(0, CVector2f(-20.0f, -40.0f));
    mPlayer1.setPoint(1, CVector2f(20.0f, -40.0f));
    mPlayer1.setPoint(2, CVector2f(20.0f, 40.0f));
    mPlayer1.setPoint(3, CVector2f(-20.0f, 40.0f));
    mPlayer1.setFillColor(CColour::Blue);
    mPlayer1.setPosition(40.0f, GameOptions::viewHeight / 2.0f);
    
    mPlayer2 = CConvexShape(4);
    mPlayer2.setPoint(0, CVector2f(-20.0f, -40.0f));
    mPlayer2.setPoint(1, CVector2f(20.0f, -40.0f));
    mPlayer2.setPoint(2, CVector2f(20.0f, 40.0f));
    mPlayer2.setPoint(3, CVector2f(-20.0f, 40.0f));
    mPlayer2.setFillColor(CColour::Red);
    mPlayer2.setPosition(GameOptions::viewWidth - 40.0f, GameOptions::viewHeight / 2.0f);
    
    mPlayer1Speed = 200.0f;
    mPlayer2Speed = 200.0f;
    
    mBall = CConvexShape(4);
    mBall.setPoint(0, CVector2f(-10.0f, -10.0f));
    mBall.setPoint(1, CVector2f(10.0f, -10.0f));
    mBall.setPoint(2, CVector2f(10.0f, 10.0f));
    mBall.setPoint(3, CVector2f(-10.0f, 10.0f));
    mBall.setFillColor(CColour::Green);
    
    mBallSpeed = 400.0f;
    
    InitialiseBallVel();
}

CPong::~CPong()
{
    SAFE_DELETE(mPauseMenu);
}

void CPong::Update(CTime elapsedTime)
{
    if (mPaused) return;

    if (CKeyboard::isKeyPressed(CKeyboard::W))
    {
        mPlayer1.move(0.0f, -mPlayer1Speed * elapsedTime.asSeconds());
    }
    if (CKeyboard::isKeyPressed(CKeyboard::S))
    {
        mPlayer1.move(0.0f, mPlayer1Speed * elapsedTime.asSeconds());
    }
    
    float xpos = mPlayer1.getPosition().x;
    float ypos = mPlayer1.getPosition().y;
    if (ypos < 0.0f)
    {
        mPlayer1.setPosition(xpos, 0.0f);
    }
    if (ypos > GameOptions::viewHeight)
    {
        mPlayer1.setPosition(xpos, GameOptions::viewHeight);
    }
    
    float ballY = mBall.getPosition().y;
    float p2X = mPlayer2.getPosition().x;
    float p2Y = mPlayer2.getPosition().y;
    float distance = fabs(p2Y - ballY);
    if (distance < (mPlayer2Speed * elapsedTime.asSeconds()))
    {
        mPlayer2.setPosition(p2X, ballY);
    }
    else if (p2Y < ballY)
    {
        mPlayer2.move(0.0f, mPlayer2Speed * elapsedTime.asSeconds());
    }
    else if (p2Y > ballY)
    {
        mPlayer2.move(0.0f, -mPlayer2Speed * elapsedTime.asSeconds());
    }
    
    mBall.move(mBallVelocity * elapsedTime.asSeconds());
    CVector2f cv;
    if (mBall.IsCollidingWith(mPlayer1, &cv) || mBall.IsCollidingWith(mPlayer2, &cv))
    {
        mBall.move(cv);
        if (cv.x != 0)
        {
            mBallVelocity.x = -mBallVelocity.x;
        }
        if (cv.y != 0)
        {
            mBallVelocity.y = -mBallVelocity.y;
        }
    }
    xpos = mBall.getPosition().x;
    ypos = mBall.getPosition().y;
    if (ypos < 0.0f)
    {
        mBallVelocity.y = -mBallVelocity.y;
        mBall.setPosition(xpos, 0.1f);
    }
    else if (ypos > GameOptions::viewHeight)
    {
        mBallVelocity.y = -mBallVelocity.y;
        mBall.setPosition(xpos, GameOptions::viewHeight - 0.1f);
    }
    if (xpos < 0.0f || xpos > GameOptions::viewWidth)
    {
        InitialiseBallVel();
    }
}

void CPong::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mPlayer1);
    theWindow->DrawShape(mPlayer2);
    theWindow->DrawShape(mBall);
}

void CPong::Enter()
{
    CMenuTest::Get()->RegisterRenderable(this);
    CMenuTest::Get()->RegisterUpdateable(this);
    
    CMessageBroadcaster<CEvent>::Subscribe(this);
}

void CPong::Exit()
{
    CMenuTest::Get()->UnregisterRenderable(this);
    CMenuTest::Get()->UnregisterUpdateable(this);
    
    CMessageBroadcaster<CEvent>::Unsubscribe(this);
}

bool CPong::HandleMessage(CEvent e)
{
    bool theResult = false;

    if (mPaused) return theResult;
    
    if (e.type == CEvent::KeyPressed)
    {
        if (e.key.code == CKeyboard::R)
        {
            InitialiseBallVel();
        }
        else if (e.key.code == CKeyboard::Escape)
        {
            PauseGame();
        }
    }
    
    return theResult;
}

void CPong::InitialiseBallVel()
{
    auto gen = MathsUtilities::GetRandomGeneratorFunctionForRange(-100.0f , 100.0f);
    float x = gen();
    float y = gen();
    
    mBallVelocity = CVector2f(x, y);
    mBallVelocity.Normalise();
    mBallVelocity *= mBallSpeed;
    
    mBall.setPosition(GameOptions::viewWidth / 2.0f, GameOptions::viewHeight / 2.0f);
}

void CPong::PauseGame()
{
    mPaused = true;
    mPauseMenu->Enter();
}

void CPong::UnpauseGame()
{
    mPaused = false;
    mPauseMenu->Exit();
}