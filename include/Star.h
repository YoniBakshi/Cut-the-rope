#pragma once

#include "NonPhysicsObject.h"
#include "Animation.h"

class Star : public NonPhysicsObject
{
public:
	Star();
	Star(const sf::Vector2f pos);
	~Star();

	enum Action
	{
		A_StarSpin
	};

	void setAction(int action);
	bool getEnded();
	int getAction() const { return m_action; }
	virtual void update(sf::Time deltaTime) override;

private:
	Animation       m_animation;  // current animation of the object
	int m_action = INITIALIZE_INT;
};

