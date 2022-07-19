#include "GravityChange.h"

GravityChange::GravityChange(const sf::Vector2f pos) : GravityChange()
{
	m_sprite.setPosition(pos.x,pos.y);
}

GravityChange::GravityChange()
	: setGravity(false)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_GravityCange));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

GravityChange::~GravityChange()
{
}

void GravityChange::setAction(bool isClick)
{
	if (isClick)
	{
		m_sprite.setScale(1, -1);
		setGravity = true;
	}
	else
	{
		m_sprite.setScale(1, 1);
		setGravity = false;
	}
}

bool GravityChange::getGravity() const
{
	return setGravity;
}