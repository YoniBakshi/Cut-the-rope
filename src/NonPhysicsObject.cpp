#include "NonPhysicsObject.h"

//---------------------------------- Const Section -------------------------------------
const auto DEG_90 = 90,
		   DEG_180 = 180,
		   DEG_270 = 270;

sf::Vector2f NonPhysicsObject::getAngleDirction(const float angle)
{
	//Calculate received angles to 
	sf::Vector2f candyDir;

	if (0 < angle && angle < DEG_90)
		candyDir.x = angle, candyDir.y	= -angle;
	else if (DEG_90 < angle && angle   <= DEG_180)
		candyDir.x = -angle, candyDir.y = -angle;
	else if (DEG_180 < angle && angle   < DEG_270)
		candyDir.x = -angle, candyDir.y = angle;
	else if (DEG_270 < angle && angle   < DEG_360)
		candyDir.x = angle, candyDir.y  = angle;
	else if ((int)angle % DEG_360 == 0)
		candyDir.x = DEG_360, candyDir.y = angle;
	else if ((int)angle % DEG_360 == DEG_180)
		candyDir.x = -angle, candyDir.y  = 0;
	else if ((int)angle % DEG_360 == DEG_270)
		candyDir.x = 0, candyDir.y		 = angle;
	else if ((int)angle % DEG_360 == DEG_90)
		candyDir.x = 0, candyDir.y		 = -angle;

	return candyDir;
}
