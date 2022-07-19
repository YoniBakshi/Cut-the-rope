#include"Spike.h"

Spike::Spike(const sf::Vector2f pos , const float angle) : Spike()
{
	m_sprite.setPosition(pos);
	m_sprite.setRotation(angle);
}

Spike::Spike()
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_Spike));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

Spike::~Spike()
{
}
