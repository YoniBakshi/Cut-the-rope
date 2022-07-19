#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "box2d/box2d.h"
#include "Resources.h"

const int FROG		  = 0,
		  CANDY		  = 1,
		  LIMIT		  = 2,
		  ROPE		  = 3,//1
		  ROPE_BASE	  = 4,
		  STAR		  = 5,//1
		  SPIKE		  = 6,// 2
		  TELEPORT	  = 7,//
		  BLOWER	  = 8,// 2
		  BUBBLE	  = 9,//1 2
		  GRAVITY_SET = 10;//

const int WINDOW_WIDTH   = 1920,
		  WINDOW_HEIGHT  = 1080,
		  RESET_INDEX	 = 0,
		  DEG_360	     = 360,
		  TWO_DIGITS_DOT = 100,
		  INITIALIZE_INT = 0;

const float INITIALIZE = 0.f,
			FLOOR_LIMIT = 270.f,
			PIC_SIZE	= 70.f,
			TIMESTEP = 1.0f / 60.0f,
		    GRAVITY_SCALE = 10.f;

const int32 VELOCITYITERATIONS = 6,			// velocity of the world
			POSITIONITERATIONS = 2;			// position iterations of the world

const b2Vec2 GRAVITY = b2Vec2(0.0f, 10.0f);

struct LevelData
{
	unsigned int _level		= RESET_INDEX; 
	float		 _time		= INITIALIZE,
				 _timeLeft	= INITIALIZE;
};

enum class Buttons
{
	b_Start,
	b_Help,
	b_Exit,
	b_Back,
	b_Reset,
	b_Total
};

const auto STAND = sf::Vector2f(0, 0);

const sf::Color NON_TRANSPARENT	   = sf::Color   (255, 255, 255),
				PARTLY_TRANSPARENT = sf::Color	 (255, 255, 255, 150);

const float INCREASE_BUTTON = 1.12f,
			ORIGINAL_BUTTON = 1.0f;

#ifndef PI
// This will create a definition for PI.
#define PI 3.14f
#endif
#ifndef RADTODEG
// This will allow for the easy conversion between radians to degrees; (Multiply origional value by this).
#define RADTODEG 180 / PI
#endif 