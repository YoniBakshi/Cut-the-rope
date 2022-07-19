#include "DataToolBar.h"

//---------------------------------- Const Section-------------------------------------
const std::string LEVEL		  = "Level : ",
				  TIME		  = "Time : ",
				  TIME_LEFT	  = "Time Left : ",
				  NOT_LIMITED = " - ";
const auto		  TIME_LOW    = 10;

DataToolBar::DataToolBar() 
	: m_animation(Resources::instance().animationData((int)Resources::Object::o_StarScore), m_starScore),
	  m_action(INITIALIZE)
{
	configureTextMembers();
	configureSpriteMembers();
	pushButtonToolBar();
}

DataToolBar::~DataToolBar()
{
}

void DataToolBar::drawDataToolBar(sf::RenderWindow& window) const
{
	for (int i = 0; i < m_buttonsToolBar.size(); ++i)
		m_buttonsToolBar[i]->drawButton(window);

	window.draw(m_timeText);
	window.draw(m_levelText);
	window.draw(m_timeLeftText);
	window.draw(m_starScore);
}

void DataToolBar::updateDataToolBar(sf::Time deltaTime, const LevelManager& levelData)
{
	m_lvlData._level = levelData.getLevelNumber();
	updateText();
	updateTime(deltaTime, levelData);
	updatePosition();
}

int DataToolBar::checkClick(sf::Vector2f currLoc)
{
	int i = INITIALIZE;

	for (auto& stat : m_buttonsToolBar)
		if (stat->checkContain(currLoc))
			return i;

	return -1;
}

void DataToolBar::setAction(int action)
{
	m_action = action;
	if (action == A_0StarScore)
		m_animation.action(Action::A_0StarScore);
	else if (action == A_1StarScore)
		m_animation.action(Action::A_1StarScore);
	else if (action == A_2StarScore)
		m_animation.action(Action::A_2StarScore);
	else if (action == A_3StarScore)
		m_animation.action(Action::A_3StarScore);
}

void DataToolBar::update(sf::Time deltaTime)
{
	m_animation.update(deltaTime);
}

void DataToolBar::resetDataToolBar()
{
	m_resetTimer		= true;
	m_lvlData._timeLeft = INITIALIZE;
	m_lvlData._time		= INITIALIZE;
	m_lvlData._level	= INITIALIZE;
}

void DataToolBar::updatePosition()
{
	m_levelText.setOrigin(m_levelText.getGlobalBounds().width / 2,		 m_levelText.getGlobalBounds().height / 2);
	m_timeText.setOrigin(m_timeText.getGlobalBounds().width / 2,		 m_timeText.getGlobalBounds().height / 2);
	m_timeLeftText.setOrigin(m_timeLeftText.getGlobalBounds().width / 2, m_timeLeftText.getGlobalBounds().height / 2);
	m_starScore.setOrigin(m_starScore.getGlobalBounds().width / 2,		 m_starScore.getGlobalBounds().height / 2);

	m_levelText.setPosition(WINDOW_WIDTH / 14,			 WINDOW_HEIGHT / 13 - PIC_SIZE / 1.8);
	m_timeText.setPosition(WINDOW_WIDTH / 4,			 WINDOW_HEIGHT / 13 - PIC_SIZE / 1.8);
	m_starScore.setPosition(WINDOW_WIDTH - 5 * PIC_SIZE, WINDOW_HEIGHT / 19);
	m_timeLeftText.setPosition(WINDOW_WIDTH / 7.5,		 WINDOW_HEIGHT / 1.1 + PIC_SIZE / 1.6);
}

void DataToolBar::updateText()
{
	m_levelText.setString(LEVEL + std::to_string(m_lvlData._level));
	m_timeText.setString (TIME + std::to_string(m_lvlData._time));
}

void DataToolBar::updateTime(sf::Time deltaTime, const LevelManager& levelData)
{
	m_lvlData._time += deltaTime.asSeconds();
	auto afterDotTime = (m_lvlData._time * TWO_DIGITS_DOT);
	m_timeText.setString(TIME + std::format("{}.{}", std::to_string((int)(m_lvlData._time)), std::to_string(((int)afterDotTime) % TWO_DIGITS_DOT)));

	if (levelData.isHaveTimer())
	{
		if (m_resetTimer)
		{
			m_lvlData._timeLeft = levelData.getTimer();
			m_resetTimer = false;
		}
		m_lvlData._timeLeft -= deltaTime.asSeconds();
		auto afterDotTimeLeft = (m_lvlData._time * TWO_DIGITS_DOT);
		m_timeLeftText.setString(TIME_LEFT + std::format("{}.{}", std::to_string((int)(m_lvlData._timeLeft)), std::to_string(((int)afterDotTimeLeft) % TWO_DIGITS_DOT)));

		if (m_lvlData._timeLeft <= TIME_LOW)
			m_timeLeftText.setFillColor(sf::Color::Red);
		else
			m_timeLeftText.setFillColor(sf::Color::Black);
	}
	else
		m_timeLeftText.setString(TIME_LEFT + NOT_LIMITED);
}

void DataToolBar::configureTextMembers()
{
	Resources& inst = Resources::instance();

	inst.configureText(m_levelText,    sf::Color::Black, sf::Color::White);
	inst.configureText(m_timeText,     sf::Color::Black, sf::Color::White);
	inst.configureText(m_timeLeftText, sf::Color::Black, sf::Color::White);
}

void DataToolBar::configureSpriteMembers()
{
	m_starScore.setTexture(Resources::instance().getTexture(Resources::Textures::t_StarScore));
	m_animation.action(Action::A_0StarScore);
}

void DataToolBar::pushButtonToolBar()
{
	m_buttonsToolBar.push_back(std::make_unique<Button>(Resources::Textures::t_Reset, Buttons::b_Reset));
	m_buttonsToolBar[INITIALIZE]->setPosition({ WINDOW_WIDTH - 1.2 * PIC_SIZE, WINDOW_HEIGHT / 18 });
}
