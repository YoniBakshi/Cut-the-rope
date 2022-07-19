#pragma once
#include <vector>

#include "Macros.h"
#include "Button.h"
#include "Collision.h"

class Menu
{
public:
	Menu(const sf::RenderWindow& window);
	~Menu();

	void drawMenu(sf::RenderWindow& window) const;
	void updateMenu(sf::Vector2f& point);
	void resetMenu();
	void handleClick(sf::RenderWindow& window, const Button& buttonClicked);
	bool isMenuRunning() const;
	void handleMouseEvents(sf::RenderWindow& window);

private:
	std::vector<std::unique_ptr<Button>> m_buttons;
	sf::RectangleShape					 m_menuBackground;
	sf::Sprite						     m_helpData;  

	sf::Sound m_buttonSound;
	sf::Sound m_byeByeSound;;
	sf::Sound m_startKnockSound;
	sf::Sound m_doorOpenSound;
	
	sf::Text	 m_createdBy;
	sf::Listener m_sounds;          // Controlls all the sounds 

	void openHelpMenu(sf::RenderWindow& window) const;
	bool m_isRunning = true;
};

