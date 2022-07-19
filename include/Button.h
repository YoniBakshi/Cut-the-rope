#pragma once

#include "Macros.h"

class Button
{
public:
	Button(Resources::Textures index, Buttons indexButton);
	~Button();

	void drawButton(sf::RenderWindow& window) const;
	void setPosition(sf::Vector2f pos);
	void resetButtons();
	bool checkContain(sf::Vector2f& point) const;
	void handleContain();
	Buttons getIndexButton() const;
	sf::Sprite getButtonSprite() const;

private:
	sf::Sprite m_button;
	Buttons m_indexButton;
};

