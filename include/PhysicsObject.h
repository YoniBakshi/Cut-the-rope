#pragma once

#include "GameObject.h"
#include "NonPhysicsObject.h"

class PhysicsObject : public GameObject
{
public:
	virtual ~PhysicsObject() = default;

	virtual void createBody(b2World* world, sf::Vector2f position, bool stati, sf::Vector2f size = { 15, 1 });
	void destroyBody();
	sf::Vector2f convertb2Vec2ToVec2f(b2Vec2 pos) const;
	b2Body* getBody() const;

protected:
	b2Body* m_body	  = nullptr;			// The box2D body of the object
	bool m_teleported = false;
	bool m_onTeleport = false;

private:
	
};