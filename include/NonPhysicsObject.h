#pragma once

#include "GameObject.h"

class NonPhysicsObject : public GameObject
{
public:
	virtual ~NonPhysicsObject() = default;
	
	sf::Vector2f getAngleDirction(const float angle);
	virtual void update(sf::Time) {}
	
protected:

private:

};

