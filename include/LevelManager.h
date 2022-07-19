#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Macros.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void  resetLevelManager();
	bool  isHaveTimer()    const;
	bool  scanBoardFile();
	int   getLevelNumber() const;
	float getTimer()       const;						//Get limited time for level.
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getCurrentMapVec() const;

private:
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_vecObjectData;
	std::vector<std::string> m_levelFilesNames;

	LevelData m_lvlData;

	bool m_haveTimer;
};

