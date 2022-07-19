#include "PhysicsObject.h"

//---------------------------------- Const Section-------------------------------------
const auto DENSITY	= 0.3f, 
		   FRICTION = 0.7f,
		   MASS		= 9.f;

//create a box2d body for the movable (dynamic)
void PhysicsObject::createBody(b2World* world, sf::Vector2f position, bool stati, sf::Vector2f size)
{
	b2BodyDef bodyDef;

	if (stati)
		bodyDef.type = b2_staticBody;
	else 
		bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(position.x, position.y);
	m_body = world->CreateBody(&bodyDef);
	m_body->SetGravityScale(10);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((float)m_sprite.getTexture()->getSize().x / 4, (float)m_sprite.getTexture()->getSize().y / 4);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.filter.groupIndex = -1;
	fixtureDef.friction = FRICTION;
	fixtureDef.density = DENSITY;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetFixedRotation(true);
	m_body->SetSleepingAllowed(false);

	b2MassData massa;
	massa.mass = MASS;
	massa.center = m_body->GetLocalCenter();
	m_body->SetMassData(&massa);

	m_sprite.setPosition(convertb2Vec2ToVec2f(m_body->GetPosition()));
}

sf::Vector2f PhysicsObject::convertb2Vec2ToVec2f(b2Vec2 pos) const { return sf::Vector2f({ pos.x , pos.y }); }

b2Body* PhysicsObject::getBody() const { return m_body; }

void PhysicsObject::destroyBody() { m_body = nullptr; }
