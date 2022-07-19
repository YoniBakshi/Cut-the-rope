#include "Bubble.h"

Bubble::Bubble(const sf::Vector2f pos) : Bubble()
{
	m_sprite.setPosition(pos);
}

Bubble::Bubble()
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_Bubble));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

Bubble::~Bubble()
{
}