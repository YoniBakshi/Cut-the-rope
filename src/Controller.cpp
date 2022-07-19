#include "Controller.h"

Controller::Controller()
	: m_menu(m_window), m_run(false), m_mode(t_Menu)
{
	m_startMsg.setTexture(Resources::instance().getTexture(Resources::Textures::t_StartMsg));
	m_levelUpMsg.setTexture(Resources::instance().getTexture(Resources::Textures::t_LevelUpMsg));
	m_loseMsg.setTexture(Resources::instance().getTexture(Resources::Textures::t_LoseMsg));
	m_winMsg.setTexture(Resources::instance().getTexture(Resources::Textures::t_WinMsg));
}

void Controller::run()
{
	while (m_window.isOpen())
	{
		runMenu();
		runGame();
	}
}

void Controller::runMenu()
{
	m_menu.resetMenu();

	while ((m_window.isOpen()) && (m_menu.isMenuRunning()))
	{
		m_window.clear();
		m_menu.drawMenu(m_window);
		m_window.display();
		m_menu.resetMenu();
		m_menu.handleMouseEvents(m_window);
	}
}

void Controller::runGame()
{
	setGame();

	while (m_window.isOpen())
	{
		switch (m_mode)
		{
		case t_Play:
			playingMode();
			break;
		case t_Menu:
			return;
		case t_LevelUP:
		case t_Lose:
		case t_FinishScreen:
			gameMessage();
			break;
		default:
			break;
		}
		handleEvents();
	}
}

void Controller::setGame()
{
	m_mode = t_Play;
	m_world.playGameMusic();
	m_window.draw(m_startMsg);
	m_window.display();
	sf::sleep(sf::seconds(3));					//Sleep for 3 seconds so texture will stay on screen
	m_gameClock.restart();
	m_world.resetLevel();
	m_run = m_world.updateLevel();
	m_window.setFramerateLimit(100);
}

void Controller::playingMode()
{
	if (!m_world.isLevelRunning())			// Level ends
	{
		if (!m_world.updateLevel())			// New level NOT readed successfuly
		{
			m_mode = t_FinishScreen;
			return;
		}

		m_mode = t_LevelUP;
		m_gameClock.restart();
		return;
	}
	else
		m_world.stepBox2dWorld();			//update box2d objects

	if (m_world.getIsLose())				//IF lose is up
	{
		Resources::instance().playSound((int)Resources::Sounds::s_LoseCartoon);
		m_mode = t_Lose;

		if (!m_world.updateLevel())			// New level NOT readed successfuly
			m_mode = t_Menu;
		return;
	}

	draw();
	updateGameObjects();
}

void Controller::draw()
{
	m_window.clear();
	switch (m_mode)
	{
	case t_Play:
		m_world.drawWorld(m_window, m_gameClock.restart());
		break;
	case t_LevelUP:
		m_window.draw(m_levelUpMsg);
		break;
	case t_Lose:
		m_window.draw(m_loseMsg);
		break;
	case t_FinishScreen:
		m_window.draw(m_winMsg);
		break;
	default:
		break;
	}
	m_window.display();
}

void Controller::handleEvents()
{
	for (auto event = sf::Event(); m_window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			Resources::instance().getGameMusic().stop();
			Resources::instance().playSound((int)Resources::Sounds::s_ByeBye);
			m_window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				Resources::instance().getGameMusic().stop();
				Resources::instance().playSound((int)Resources::Sounds::s_ByeBye);
				m_window.close();
				break;
			}

			else if (event.key.code == sf::Keyboard::M)
			{
				m_sounds.setGlobalVolume((m_sounds.getGlobalVolume() > 0.f) ? 0.f : 50.f);
				break;
			}
			else if (event.key.code == sf::Keyboard::B)
			{
				m_mode = t_Menu;
				break;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				switch (m_mode) {
				case t_LevelUP: m_mode = t_Play; break;
				case t_Lose: m_mode = t_Play; break;
				case t_FinishScreen: m_mode = t_Menu; break;
				}
			}
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_posStartClick = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				break;
			}
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_posEndClick = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				m_world.handleClick(m_posStartClick, m_posEndClick);
				break;
			}
		default:
			break;
		}
	}
}

void Controller::updateGameObjects()
{
	const auto deltaTime = m_gameClock.restart();
	m_world.updateWorld(deltaTime);
}

void Controller::WinScreen()
{
	Resources::instance().playSound((int)Resources::Sounds::s_WinYay);
	draw();
	sf::sleep(sf::seconds(8));						// Sleep for 8 seconds so texture will stay on screen
	Resources::instance().getGameMusic().stop();
	Resources::instance().getMenuMusic().play();
	m_mode = t_Menu;
}

void Controller::gameMessage()
{
	switch (m_mode)
	{
	case t_LevelUP:
		m_gameClock.restart();
		draw();
		break;
	case t_Lose:
		m_gameClock.restart();
		draw();
		break;
	case t_FinishScreen:
		WinScreen();
		break;
	default:
		break;
	}
}