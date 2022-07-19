#include "Rope.h"
#include "box2d/b2_rope.h"

//---------------------------------- Const Section-------------------------------------
const auto DENSITY = 0.3f,
FRICTION = 0.9f,
RESTI = 0.3f;

Rope::Rope()
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_Rope));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

Rope::Rope(const sf::Vector2f pos) : Rope()
{
	m_sprite.setPosition(pos);
}

Rope::~Rope()
{
}

/* Create Rope : This will be used to create a rope between two objects.
* Param One - b2Body : This will be the first body in the chain.
* Param Two - float : This will be the number of segments to add, thus the length of the rope.
* Param Three - b2Body : The last body the rope connects to.
* Param Four - b2World : The physics world the items will be added to.
* Param Five - b2Vec2 : The first anchor point for the first body.
* Param Six - The final ancor point for the final body. */
void Rope::createRope(b2Body* firstBody, int iNumberOfSegments, b2Body* finalBody, b2World* world, b2Vec2 initialAnchor, b2Vec2 finalAnchor)
{
	m_ropeSegments.clear();
	m_ropeBoxes.clear();

	// Create Body Def for the segments. 
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(initialAnchor.LengthSquared(), initialAnchor.y);

	// Create the shape for the rope. 
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(2.f, 2.f);

	// Create a Fixture Def for the segments. 
	b2FixtureDef fixtureDef = creatFixtureDef();
	fixtureDef.shape = &polygonShape;

	// Create the joint. 
	b2RevoluteJointDef revoluteJointDef = creatJoint();

	// Assign body to be the first body (A static object in the level). 
	b2Body* preveousBody = firstBody;
	m_ropeSegments.push_back(preveousBody);

	// Create SFML rectangle object. 
	sf::RectangleShape box;
	box.setSize(sf::Vector2f(15.f, 15.f));
	box.setOrigin(7.5f, 7.5f);

	// Create n number of rope segments.
	for (int i = 0; i < iNumberOfSegments; i++)
	{
		if (i == 0)
			bodyDef.position.Set(initialAnchor.x, initialAnchor.y);
		else if (i == iNumberOfSegments - 1)
			bodyDef.position.Set(finalAnchor.x, finalAnchor.y);
		else
		{
			bodyDef.position.Set(initialAnchor.x, initialAnchor.y);
			box.setSize(sf::Vector2f(25.f, 15.f));
			box.setOrigin(12.5f, 7.5f);

		}

		// New body for the rope. 
		b2Body* newBody = world->CreateBody(&bodyDef);
		newBody->CreateFixture(&fixtureDef);
		newBody->SetGravityScale(3);
		m_ropeSegments.push_back(newBody);
		revoluteJointDef.bodyA = preveousBody;
		revoluteJointDef.bodyB = newBody;
		world->CreateJoint(&revoluteJointDef);

		// Make the newly created object become the preveous body. 
		preveousBody = newBody;

		// Set the anchor points for the initial two bodies. 
		revoluteJointDef.localAnchorA.Set(preveousBody->GetPosition().x / 100, preveousBody->GetPosition().y / 100 -2);
		revoluteJointDef.localAnchorB.Set(0.5, 0);

		// Add a new box for the new rope segment. 
		m_ropeBoxes.push_back(box);
	}

	// Create Final Joint.
	revoluteJointDef.localAnchorA.Set(preveousBody->GetPosition().x / 100, preveousBody->GetPosition().y / 100-2);
	revoluteJointDef.localAnchorB.Set(0.5, 0);

	revoluteJointDef.bodyA = preveousBody;
	revoluteJointDef.bodyB = finalBody;

	world->CreateJoint(&revoluteJointDef);
	assignTexture();
}

/* Draw Rope : This will be used to draw the rope segments into the window.
 * Param One - RenderWindow : this will be the window the item will be drawn onto. */
void Rope::drawRope(sf::RenderWindow& window)
{
	for (auto& i : m_ropeBoxes)
		window.draw(i);
}

//Update Rope : This will be used to update the position of the rope segments.
void Rope::updateRope()
{
	for (unsigned int i = 0; i < m_ropeSegments.size() - 1; i++)
	{
		m_ropeSegments.at(i)->SetAngularDamping(0.0001f);
		m_ropeSegments.at(i)->SetAngularVelocity(0.001f);
		m_ropeBoxes.at(i).setPosition(sf::Vector2f(m_ropeSegments.at(i)->GetPosition().x, m_ropeSegments.at(i)->GetPosition().y));
		m_ropeBoxes.at(i).setRotation(m_ropeSegments.at(i)->GetAngle() * RADTODEG);
	}

	if (m_ropeSegments.size() != m_ropeBoxes.size() + 1)
		m_ropeBoxes.pop_back();
}

/* Assign Texture : This will assign a texture to the object's shape.
 * Param One - Texture : This will be the new texture for the shape. */

void Rope::assignTexture()
{
	for (auto& i : m_ropeBoxes)
		i.setTexture(&(Resources::instance().getTexture(Resources::Textures::t_Rope)));
}

void Rope::eraseRope(b2World* world)
{
	for (auto& i : m_ropeSegments)
		if (i)
			world->DestroyBody(i);

	m_ropeBoxes.clear();
}

std::vector<sf::RectangleShape> Rope::getRopeBoxes() const
{
	return m_ropeBoxes;
}

b2FixtureDef Rope::creatFixtureDef()
{
	// Create a Fixture Def for the segments. 
	b2FixtureDef fixtureDef;
	fixtureDef.density = DENSITY;
	fixtureDef.friction = FRICTION;
	fixtureDef.restitution = RESTI;
	fixtureDef.filter.groupIndex = -1;
	return fixtureDef;
}

b2RevoluteJointDef Rope::creatJoint()
{
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.collideConnected = true;
	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 0.9f;
	revoluteJointDef.referenceAngle = 0.9f;
	revoluteJointDef.upperAngle = .9f;
	revoluteJointDef.motorSpeed = 10.f;
	return revoluteJointDef;
}