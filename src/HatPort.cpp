#include "HatPort.h"

HatPort::HatPort(const sf::Vector3f& currentLocTP, const sf::Vector3f& pairLocationTP) :HatPort()
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_HatPort));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(currentLocTP.x, currentLocTP.y);
	m_sprite.setRotation(-currentLocTP.z);
	m_pairLocationTP = pairLocationTP;
}

HatPort::~HatPort()
{
}

//Return the location of paired teleport (the other teleport object location)
sf::Vector3f HatPort::getPairsPositionTP() const
{
	return m_pairLocationTP;
}
