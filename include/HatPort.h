#pragma once

#include "NonPhysicsObject.h"

class HatPort : public NonPhysicsObject
{
public:
	HatPort() {};
	HatPort(const sf::Vector3f& currentLocTP, const sf::Vector3f& pairLocationTP);
	~HatPort();

	sf::Vector3f getPairsPositionTP() const;

private:
	std::vector<sf::Vector3f> m_teleportPair;
	sf::Vector3f m_pairLocationTP;
};

