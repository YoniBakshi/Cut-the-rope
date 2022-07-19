#pragma once

#include "Macros.h"					// contain include for Resources aswell
#include "Blower.h"
#include "Frog.h"
#include "LevelManager.h"
#include "NonPhysicsObject.h"
#include "PhysicsObject.h"
#include "GameObject.h"
#include "HatPort.h"
#include "Spike.h"
#include "Candy.h"
#include "Rope.h"
#include "RopeBase.h"
#include "Limit.h"
#include "Bubble.h"
#include "Star.h"
#include "CollisionHandling.h"
#include "DataToolBar.h"
#include "GravityChange.h"
#include "MouseTool.h"

class World
{
public:
	enum Action
	{
		A_Level1,
		A_Level2,
		A_Level3,
		A_Level4
	};

	World();
	~World();

	void drawWorld(sf::RenderWindow& window, sf::Time deltaTime);
	void updateWorld(sf::Time deltaTime);		//Update level's objects
	bool updateLevel();							//No const - Update level and return a bool value if update succeed 
	bool isLevelRunning() const;
	void playGameMusic()  const;
	bool getIsLose()	  const;
	void resetLevel();					
	void stepBox2dWorld();
	void handleClick(sf::Vector2f posStart, sf::Vector2f  posEnd);
	void resetData();

private:
	//type conversion funcs
	sf::Vector2f convertb2Vec2ToVec2f(b2Vec2) const;

	void setAction(int action);
	void resetCandy();
	void resetMembers();

	sf::Sprite m_gameBackground;

	bool m_isLose;
	bool m_isLvlRunning;
	bool m_isReset;

	std::vector<std::unique_ptr<NonPhysicsObject>> m_NonPhysicsObjV;
	std::vector<Rope> m_ropesV;
	NonPhysicsObject* m_ptrFrog;
	LevelManager	  m_levelManager;
	Candy			  m_candy;
	b2World			  m_world;
	DataToolBar		  m_dataToolBar;
	LevelData		  m_lvlData;
	MouseTool		  m_mouseTool;
	Animation         m_animation;  // current animation of the object

	int m_numOfRopes;
};
