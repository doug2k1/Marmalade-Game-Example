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
#include "IwGx.h"
#include "Iw2D.h"
#include "IwResManager.h"
#include "IwSound.h"
#include "game.h"

CGame::CGame()
: m_Position(0,0)
, m_Size(Iw2DGetSurfaceHeight() / 10, Iw2DGetSurfaceHeight() / 10)
, m_UpdatesPerSec(0)
, m_TimeToOneSec(0)
, m_CountUpdates(0)
{
	s3eAudioPlay("birds.mp3", 0);

	m_SndExplosion = (CIwSoundSpec*)IwGetResManager()->LoadGroup("sounds.group")->GetResNamed("explosion", IW_SOUND_RESTYPE_SPEC);

	// text
	IwGetResManager()->LoadGroup("fonts.group"); 
	m_Font = Iw2DCreateFontResource("font"); 
	Iw2DSetFont(m_Font); 

	// sprites
	IwGetResManager()->LoadGroup("sprites.group");
	m_Pig = new GameEntity("pig"); 
	m_Pig->SetCenter(CIwSVec2(50,50));
	m_Target = new GameEntity("guide"); 
	m_Target->SetCenter(CIwSVec2(50,50));
	m_Target->SetPosition(CIwFVec2(480,320));
	m_Sonic = new GameEntity("sonic");
	m_Sonic->SetAnimated(true, 15, CIwSVec2(4,1));
	m_Sonic->SetMovSpeed(CIwFVec2(600,0));

	m_LastUpdate = s3eTimerGetMs();
}


CGame::~CGame()
{
	delete m_Font;
	delete m_Pig;
	delete m_Target;
	delete m_Sonic;
	s3eAudioStop();
}


void CGame::Update()
{
    // game logic goes here
	uint64 deltaTime = s3eTimerGetMs() - m_LastUpdate;
	m_LastUpdate = s3eTimerGetMs();
	float dtSecs = deltaTime * 0.001f;

	m_TimeToOneSec += deltaTime;

	if (m_TimeToOneSec >= 1000) 
	{ 
		m_TimeToOneSec -= 1000; 
		m_UpdatesPerSec = m_CountUpdates;
		m_CountUpdates = 0;
	}

	m_CountUpdates++;

    // for example, move a red square towards any touch event...
    if( s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) & S3E_POINTER_STATE_DOWN )
    {
        CIwFVec2 target((float)s3ePointerGetX(), (float)s3ePointerGetY());
        m_Position += (target - m_Position) * 5 * dtSecs;
		m_Pig->SetPosition(m_Position);
		m_Target->SetRotation(IwGeomAtan2(int(m_Target->GetPosition().x - target.x), int(-m_Target->GetPosition().y + target.y)) + IW_ANGLE_FROM_DEGREES(180));
	}

	if( s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) & S3E_POINTER_STATE_PRESSED )
	{
		m_SndExplosion->Play();
	}

	m_Sonic->Update(dtSecs);

	if (m_Sonic->GetPosition().x > 1000)  
	{
		m_Sonic->SetPosition(CIwFVec2(0, m_Sonic->GetPosition().y));
	}

	m_Pig->Update(dtSecs);

	// Update Iw Sound Manager
	IwGetSoundManager()->Update();
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
	Iw2DDrawString("Game Test", CIwSVec2(10,10), CIwSVec2(400,100), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP); 
	char buffer [50];
	sprintf(buffer, "FPS: %d", m_UpdatesPerSec);
	Iw2DDrawString(buffer, CIwSVec2(10,30), CIwSVec2(400,100), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);

    // show the surface
    Iw2DSurfaceShow();
}
