/*
 * This file is part of the Marmalade SDK Code Samples.
 *
 * Copyright (C) 2001-2011 Ideaworks3D Ltd.
 * All Rights Reserved.
 *
 * This source code is intended only as a supplement to Ideaworks Labs
 * Development Tools and/or on-line documentation.
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */
#include "s3e.h"
#include "Iw2D.h"
#include "IwResManager.h"
#include "game.h"

CGame::CGame()
: m_Position(0,0)
, m_Size(Iw2DGetSurfaceHeight() / 10, Iw2DGetSurfaceHeight() / 10)
{
	s3eAudioPlay("birds.mp3", 0);
	IwGetResManager()->LoadGroup("sprites.group");
	m_Pig = new GameEntity("pig"); 
	m_Pig->SetCenter(CIwSVec2(50,50));
	m_Target = new GameEntity("guide"); 
	m_Target->SetCenter(CIwSVec2(50,50));
	m_Target->SetPosition(CIwSVec2(480,320));
	m_Sonic = new GameEntity("sonic");
	m_Sonic->SetAnimated(true, CIwSVec2(4,1));

	m_LastUpdate = s3eTimerGetMs();
}


CGame::~CGame()
{
	delete m_Pig;
	delete m_Target;
	delete m_Sonic;
	s3eAudioStop();
}


void CGame::Update()
{
    // game logic goes here
	int deltaTime = s3eTimerGetMs()- m_LastUpdate;
	m_LastUpdate = s3eTimerGetMs();

    // for example, move a red square towards any touch event...
    if( s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) & S3E_POINTER_STATE_DOWN )
    {
        CIwFVec2 target((float)s3ePointerGetX(), (float)s3ePointerGetY());
        m_Position += (target - m_Position) * 0.05f;
		m_Pig->SetPosition(CIwSVec2(m_Position.x, m_Position.y));
		m_Target->SetRotation(IwGeomAtan2(m_Target->GetPosition().x - target.x, -m_Target->GetPosition().y + target.y) + IW_ANGLE_FROM_DEGREES(180));
    }

	m_Sonic->Update(deltaTime);
}


void CGame::Render()
{
    // game render goes here

    // for example, clear to black (the order of components is ABGR)
    Iw2DSurfaceClear(0xff000000);

    // draw a red square
    //Iw2DSetColour(0xff0000ff);
    
    // note conversion to pixel coordinates
    //Iw2DFillRect(CIwSVec2((iwsfixed)m_Position.x, (iwsfixed)m_Position.y) - m_Size/IW_FIXED(2), m_Size);

	m_Target->Draw();
	m_Pig->Draw();
	m_Sonic->Draw();

    // show the surface
    Iw2DSurfaceShow();
}
