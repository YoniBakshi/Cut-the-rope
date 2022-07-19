#pragma once

#include "NonPhysicsObject.h"


class GravityChange : public NonPhysicsObject
{
public:
	GravityChange(const sf::Vector2f pos);
	GravityChange();
	~GravityChange();

	void setAction(bool isClick);
	bool getGravity() const;

private:
	bool setGravity;
	sf::RectangleShape m_blowZone;

};

