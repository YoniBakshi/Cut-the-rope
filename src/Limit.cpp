#include"Limit.h"

Limit::Limit(const sf::Vector2f pos, bool rotate) : Limit()
{
	m_sprite.setPosition(pos);

	if(rotate)
		m_sprite.setRotation(90.f);
}

Limit::Limit()
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_Limit));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

Limit::~Limit()
{
}