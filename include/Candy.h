#pragma once

#include "PhysicsObject.h"
#include "Animation.h"

class Candy : public PhysicsObject
{
public:
	enum Action
	{
		A_Candy,
		A_CandyBroken
	};

	Candy(const sf::Vector2f pos);
	Candy();
	~Candy();

	void setCandyBubbled(bool isBubbled);
	bool getCandyBubbled() const;

	void setCandyOnTeleport(bool onTeleport);
	bool getCandyOnTeleport() const;

	void setCandyTeleported(bool onTeleport);
	bool getCandyTeleported() const;

	void setCandyLost(bool candyLost);
	bool isCandyLost() const;

	void setCandy2Rope(bool candyattached);
	bool isCandy2Rope() const;

	void setCandyGravity(bool Gravity);
	bool isCandyGravity() const;

	void setStar();
	void initializeStarScore();
	unsigned int getStarScore() const;

	bool getDeleteCandy() const;
	void setDeleteCandy(bool is2Delete);

	void setAction(int action);
	bool isAnimationEnded() const;
	int getAction() { return m_action; }
	virtual void update(sf::Time deltaTime);
	void setAmountOfRope(int ropes);
	int getAmountOfRopes() const;

private:
	bool m_candyOnTeleport;
	bool m_candyTeleported;
	bool m_candyBubbled;
	bool m_candy2Rope;
	bool m_candyGravity;
	bool m_candyLost;
	bool m_deleteCandy;

	unsigned int m_starsCollected;
	int			 m_numOfRopes;
	int			 m_action;

	Animation	 m_animation;		// Current animation of the object
};

