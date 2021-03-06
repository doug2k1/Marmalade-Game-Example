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
#ifndef GAME_H
#define GAME_H

#include "GameEntity.h"

class CGame
{
public:
    CGame();
    ~CGame();

    // update will be called a fixed number of times per second 
    // regardless of visual framerate
    void Update();
    // render will be called as fast as possible (but not faster 
    // than the update rate)
    void Render();

private:
    CIwFVec2 m_Position;
    CIwSVec2 m_Size;
	GameEntity *m_Pig;
	GameEntity *m_Target;
	GameEntity *m_Sonic;
	CIw2DFont* m_Font;
	uint64 m_LastUpdate;
	CIwSoundSpec *m_SndExplosion;

	int m_TimeToOneSec;
	int m_CountUpdates;
	int m_UpdatesPerSec;
};

#endif
