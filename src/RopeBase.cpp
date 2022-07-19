#include "RopeBase.h"

RopeBase::RopeBase(const sf::Vector2f pos) : RopeBase()
{
	m_sprite.setPosition(pos);
}

RopeBase::RopeBase()
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_RopeBase));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

RopeBase::~RopeBase()
{
}
