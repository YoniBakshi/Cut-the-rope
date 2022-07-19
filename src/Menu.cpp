#include "Menu.h"
#include "Collision.h"

Menu::Menu(const sf::RenderWindow& window)
	: m_menuBackground(sf::Vector2f(window.getSize().x, window.getSize().y))
{
	Resources::instance().getMenuMusic().setLoop(true);
	Resources::instance().getMenuMusic().setVolume(40.f);

	Resources::instance().getMenuMusic().play();

	//Set details for menu's buttons
	m_menuBackground.setTexture(&Resources::instance().getTexture(Resources::Textures::t_MenuBackground));
	m_buttons.push_back(std::make_unique<Button>(Resources::Textures::t_Start, Buttons::b_Start));
	m_buttons.push_back(std::make_unique<Button>(Resources::Textures::t_Help, Buttons::b_Help));
	m_buttons.push_back(std::make_unique<Button>(Resources::Textures::t_Exit, Buttons::b_Exit));
	m_buttons.push_back(std::make_unique<Button>(Resources::Textures::t_Back, Buttons::b_Back));

	m_helpData.setTexture((Resources::instance().getTexture(Resources::Textures::t_HelpData)));
	m_helpData.setOrigin(m_helpData.getGlobalBounds().width / 2, m_helpData.getGlobalBounds().height / 2);
	m_helpData.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

	//Locate menu's buttons on screen
	sf::Vector2f loc(window.getSize().x / 1.675f, window.getSize().y / 3.36f);

	for (int i = 0; i < m_buttons.size() - 1; ++i)
	{
		switch (i)
		{
		case ((int)Buttons::b_Start):
			break;
		case ((int)Buttons::b_Help):
			loc.x -= 265;
			loc.y += 340;
			break;
		case ((int)Buttons::b_Exit):
			loc.x -= 150;
			loc.y += 190;
			break;
		default:
			break;
		}

		m_buttons[i]->setPosition(loc);
	}

	//Set details for created by line
	m_createdBy.setFont(Resources::instance().getFont(Resources::Fonts::f_CandyFont));
	m_createdBy.setCharacterSize(45);
	m_createdBy.setOutlineThickness(1);
	m_createdBy.setColor(sf::Color(234, 22, 22, 250));
	m_createdBy.setString("By : Yehonatan Bakshi  &  Hila Saadon");
	m_createdBy.setOrigin(m_createdBy.getGlobalBounds().width / 2, m_createdBy.getGlobalBounds().height / 2);

	loc.x = window.getSize().x / 2.f;
	loc.y = window.getSize().y / 1.08f;

	m_createdBy.setPosition(loc);
	m_buttons[m_buttons.size() - 1]->setPosition({ (float)window.getSize().x / 13.f, (float)window.getSize().y - PIC_SIZE * 1.6f });
}

Menu::~Menu()
{
}

void Menu::drawMenu(sf::RenderWindow& window) const
{
	window.draw(m_menuBackground);
	window.draw(m_createdBy);

	for (int i = 0; i < m_buttons.size() - 1; ++i)
		m_buttons[i]->drawButton(window);
}

void Menu::updateMenu(sf::Vector2f& point)
{
	for (int i = 0; i < m_buttons.size() - 1; ++i)
	{
		if (Collision::singlePixelTest(m_buttons[i]->getButtonSprite(), point, 0))	//If the mouse stands on button
			m_buttons[i]->handleContain();
		else
			m_buttons[i]->resetButtons();
	}
}

void Menu::resetMenu()
{
	m_isRunning = true;
}

//A button has been clicked
void Menu::handleClick(sf::RenderWindow& window, const Button& buttonClicked)
{
	switch (buttonClicked.getIndexButton())	//Verify which button was being clicked
	{
	case Buttons::b_Start:
		m_isRunning = false;
		Resources::instance().playSound((int)Resources::Sounds::s_ButtonClicked);
		Resources::instance().playSound((int)Resources::Sounds::s_KnockDoor);
		Resources::instance().playSound((int)Resources::Sounds::s_DoorOpen);
		Resources::instance().getMenuMusic().stop();
		break;

	case Buttons::b_Help:
		Resources::instance().playSound((int)Resources::Sounds::s_ButtonClicked);
		openHelpMenu(window);
		Resources::instance().playSound((int)Resources::Sounds::s_ButtonClicked);
		break;

	case Buttons::b_Exit:
		Resources::instance().getMenuMusic().stop();
		Resources::instance().getGameMusic().stop();
		Resources::instance().playSound((int)Resources::Sounds::s_ButtonClicked);
		Resources::instance().playSound((int)Resources::Sounds::s_ByeBye);
		window.close();
		break;

	default:
		break;
	}
}

bool Menu::isMenuRunning() const
{
	return m_isRunning;
}

void Menu::handleMouseEvents(sf::RenderWindow& window)
{
	sf::Vector2f location;

	for (auto event = sf::Event{}; window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			Resources::instance().playSound((int)Resources::Sounds::s_ButtonClicked);
			window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
			}

			if (event.key.code == sf::Keyboard::M)
			{
				m_sounds.setGlobalVolume((m_sounds.getGlobalVolume() > 0.f) ? 0.f : 50.f);
				break;
			}

		case sf::Event::MouseMoved:
			location = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
			updateMenu(location);
			break;

		case sf::Event::MouseButtonReleased:
			location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			for (int i = 0; i < m_buttons.size(); ++i)
				if (m_buttons[i]->checkContain(location))	//If the mouse is being contain on button's sprite
					handleClick(window, *m_buttons[i]);
			break;

		default :
			break;
		}
	}
}

void Menu::openHelpMenu(sf::RenderWindow& window) const
{
	while (window.isOpen())
	{
		sf::Vector2f location;

		window.clear();
		window.draw(m_menuBackground);
		window.draw(m_helpData);
		m_buttons[(int)Buttons::b_Back]->drawButton(window);
		window.display();

		for (auto event = sf::Event{}; window.pollEvent(event); )
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;

			case sf::Event::MouseMoved:
				location = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

				if (m_buttons[(int)Buttons::b_Back]->checkContain(location))
					m_buttons[(int)Buttons::b_Back]->handleContain();
				else
					m_buttons[(int)Buttons::b_Back]->resetButtons();
				break;

			case sf::Event::MouseButtonReleased:
				location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

				if (m_buttons[(int)Buttons::b_Back]->checkContain(location))
					return;
			}
		}
	}
}