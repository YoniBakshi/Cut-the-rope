#include "LevelManager.h"

LevelManager::LevelManager() : m_haveTimer(false)
{
	std::ifstream m_file("Board.txt");

	if (!m_file.is_open())
			throw std::invalid_argument("could not open file Board.txt");

	while (!m_file.eof())
	{
		std::string fileName;
		std::getline(m_file, fileName);

		if(!fileName.empty())				//Term to make sure no spaces are inserted to vector	
			m_levelFilesNames.push_back(fileName);
	}
}

LevelManager::~LevelManager()
{
}

bool LevelManager::scanBoardFile()
{
	if (m_lvlData._level < m_levelFilesNames.size())
	{
		std::ifstream m_currentLvlFile(m_levelFilesNames[m_lvlData._level]);

		if (!m_currentLvlFile.is_open())
			throw std::invalid_argument("could not open file" + m_levelFilesNames[m_lvlData._level]);

		m_vecObjectData.clear();

		std::string line;
		m_currentLvlFile >> m_lvlData._timeLeft;
		m_currentLvlFile.get();			//to ignore enter

		m_haveTimer = false;

		if (m_lvlData._timeLeft > 0)
			m_haveTimer = true;

		sf::Vector2f pos;
		float type = 0;
		float angle = 0;
		//Insert map board.txt to vector
		while (!m_currentLvlFile.eof())
		{
			m_currentLvlFile >> type >> angle >> pos.x >> pos.y;
			m_currentLvlFile.get();						// To ignore enter
			m_vecObjectData.push_back(std::pair(
				sf::Vector2f(pos.x, pos.y), sf::Vector2f(type, angle)));
		}

		++m_lvlData._level;
		return true;
	}
	return false;
}

void LevelManager::resetLevelManager()
{
	m_lvlData._timeLeft = INITIALIZE;
	m_lvlData._level = INITIALIZE;
	m_haveTimer = false;
}

int LevelManager::getLevelNumber() const
{
	return m_lvlData._level;
}

float LevelManager::getTimer() const
{
	return m_lvlData._timeLeft;
}

bool LevelManager::isHaveTimer() const
{
	return m_haveTimer;
}

std::vector<std::pair<sf::Vector2f, sf::Vector2f>> LevelManager::getCurrentMapVec() const
{
	return m_vecObjectData;
}
