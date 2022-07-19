#pragma once
#include <format>

#include "time.h"
#include "Macros.h"
#include "Button.h"
#include "Animation.h"
#include "LevelManager.h"

class DataToolBar
{
public:
	enum Action
	{
		A_0StarScore,
		A_1StarScore,
		A_2StarScore,
		A_3StarScore
	};

	DataToolBar();
	~DataToolBar();

	void drawDataToolBar(sf::RenderWindow& window) const;
	void updateDataToolBar(sf::Time deltaTime, const LevelManager& levelData);
	void resetDataToolBar();
	int checkClick(sf::Vector2f currLoc);

	void setAction(int action);
	int getAction() const { return m_action; }
	void update(sf::Time deltaTime);

private:
	void updateText();
	void updatePosition();
	void updateTime(sf::Time deltaTime,const LevelManager& levelData );
	void configureTextMembers();
	void configureSpriteMembers();
	void pushButtonToolBar();		

	std::vector<std::unique_ptr<Button>> m_buttonsToolBar;		
	LevelData m_lvlData;

	sf::Sprite m_starScore;

	sf::Text   m_levelText,
			   m_timeText,
			   m_timeLeftText;

	bool	   m_resetTimer = true;


	Animation  m_animation;  // current animation of the object
	int		   m_action;
};

