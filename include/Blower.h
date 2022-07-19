#pragma once

#include "NonPhysicsObject.h"
#include "Animation.h"

class Blower : public NonPhysicsObject
{
public:
	enum Action
	{
		A_Blowing,
		A_Static
	};

	Blower(const sf::Vector2f pos, const int angle);
	Blower();
	~Blower();

	sf::RectangleShape getBlowZone() const ;
	float getAngle() const;
	void setAction(bool isClick);
	virtual void update(sf::Time deltaTime) override;

private:
	float			   m_angle;
	sf::RectangleShape m_blowZone;
	Animation		   m_animation;  // current animation of the object
};

