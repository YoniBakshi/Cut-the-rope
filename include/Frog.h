#pragma once

#include "NonPhysicsObject.h"
#include "Animation.h"

class Frog : public NonPhysicsObject
{
public:
	enum Action
	{
		A_Waiting,
		A_Lose,
		A_Almost,
		A_Win
	};

	Frog(const sf::Vector2f pos);
	Frog();
	~Frog();

	sf::RectangleShape getFrogZone() const;
	bool getWin() const;
	void setWin(bool isWin);
	bool getEnded() const;
	void setAction(int action);
	int getAction() const { return m_action; }
	virtual void update(sf::Time deltaTime) override;

private:
	bool			   m_win;
	sf::RectangleShape m_frogZone;
	Animation		   m_animation;		// Current animation of the object
	int				   m_action;	
};

