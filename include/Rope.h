/* This will be used to create a rope-like object in the game world using a bunch of connected 
*  bodies, using revolute joints (Two per body; one to connect the top to the preveous body). 
*  The ropes will be dynamic and be able to vary, for example a number of segments (length) can
*  be specified. */

#pragma once

#include "PhysicsObject.h"
#include "box2d/b2_chain_shape.h"
#include "box2d/b2_edge_shape.h"

class Rope : public PhysicsObject
{
public:
	Rope();
	~Rope();

	Rope(const sf::Vector2f pos);
	// This will be used to create a rope between two bodies. 
	void createRope(b2Body* firstBody, int iNumberOfSegments, b2Body* finalBody, b2World* world, b2Vec2 initialAnchor, b2Vec2 finalAnchor);

	// This will be used to draw the rope. 
	void drawRope(sf::RenderWindow& window);

	// This will be used to update the position of the rope segments.
	void updateRope();

	// This will be used to assign a texture to the Ropes rope segmnets. 
	void assignTexture();

	void eraseRope(b2World* world);
	std::vector<sf::RectangleShape> getRopeBoxes() const;
	b2FixtureDef creatFixtureDef();
	b2RevoluteJointDef creatJoint();

private:

	// This will be used to create the rope by connecting a bundle of bodies. 
	std::vector<b2Body*> m_ropeSegments;

	// This will hold all of the rope boxes for all of the rope segemnts. 
	std::vector<sf::RectangleShape> m_ropeBoxes;
};
