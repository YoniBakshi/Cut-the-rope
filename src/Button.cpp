#include "Button.h"

Button::Button(Resources::Textures index, Buttons indexButton)
	: m_indexButton(indexButton)
{
	m_button.setTexture(Resources::instance().getTexture(index));
	m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);
}

Button::~Button()
{
}

void Button::drawButton(sf::RenderWindow& window) const
{
	window.draw(m_button);
}

void Button::setPosition(sf::Vector2f pos)
{
	m_button.setPosition(pos);
}

void Button::resetButtons()
{
	//Button return to original shape. (When mouse is NOT on it)
	m_button.setColor(NON_TRANSPARENT);
	m_button.setScale(ORIGINAL_BUTTON, ORIGINAL_BUTTON);
}

bool Button::checkContain(sf::Vector2f& point) const
{
	return m_button.getGlobalBounds().contains(point);
}

void Button::handleContain()
{
	//While mouse above a button - it become partly transparent and bigger.
	m_button.setColor(PARTLY_TRANSPARENT);
	m_button.setScale(INCREASE_BUTTON, INCREASE_BUTTON);
}

Buttons Button::getIndexButton() const
{
	return m_indexButton;
}

sf::Sprite Button::getButtonSprite() const
{
	return m_button;
}
