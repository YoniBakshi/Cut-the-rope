#include "Star.h"

Star::Star(const sf::Vector2f pos) : Star()
{
	m_sprite.setPosition(pos);
}

Star::Star()
	: m_animation(Resources::instance().animationData((int)Resources::Object::o_Star), m_sprite)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_Star));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_animation.action(Action::A_StarSpin);
}

Star::~Star()
{
}

void Star::setAction(int action)
{
	m_action = action;
	if (action == A_StarSpin)
		m_animation.action(Action::A_StarSpin);
}

bool Star::getEnded()
{
	return m_animation.animationEnded();
}

void Star::update(sf::Time deltaTime)
{
	m_animation.update(deltaTime);
}