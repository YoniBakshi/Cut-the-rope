#include "Candy.h"

Candy::Candy(const sf::Vector2f pos) : Candy()
{
	m_sprite.setPosition(pos);
}

Candy::Candy()
	: m_animation(Resources::instance().animationData((int)Resources::Object::o_Candy), m_sprite),
	m_candyOnTeleport(false), m_candyTeleported(false), m_candyBubbled(false),
	m_candy2Rope(false), m_candyGravity(false), m_candyLost(false), m_deleteCandy(false),
	m_starsCollected(INITIALIZE_INT), m_numOfRopes(INITIALIZE_INT), m_action(INITIALIZE_INT)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_Candy));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_animation.action(Action::A_Candy);

}

Candy::~Candy()
{
}

void Candy::setCandyBubbled(bool isBubbled)
{
	m_candyBubbled = isBubbled;
}

bool Candy::getCandyBubbled() const
{
	return m_candyBubbled;
}

void Candy::setCandyOnTeleport(bool onTeleport)
{
	m_candyOnTeleport = onTeleport;
}

bool Candy::getCandyOnTeleport() const
{
	return m_candyOnTeleport;
}

void Candy::setCandyTeleported(bool onTeleport)
{
	m_candyTeleported = onTeleport;
}

bool Candy::getCandyTeleported() const
{
	return m_candyTeleported;
}

void Candy::setStar()
{
	++m_starsCollected;
}

void Candy::initializeStarScore()
{
	m_starsCollected = INITIALIZE_INT;
}

unsigned int Candy::getStarScore() const
{
	return m_starsCollected;
}

bool Candy::getDeleteCandy() const
{
	return m_deleteCandy;
}

void Candy::setDeleteCandy(bool is2Delete)
{
	m_deleteCandy = is2Delete;
}

void Candy::setAction(int action)
{
	m_action = action;
	if (action == A_Candy)
		m_animation.action(Action::A_Candy);
	else if (action == A_CandyBroken)
		m_animation.action(Action::A_CandyBroken);
}

bool Candy::isAnimationEnded() const
{
	return m_animation.animationEnded();
}

void Candy::update(sf::Time deltaTime)
{
	m_animation.update(deltaTime);
}

void Candy::setAmountOfRope(int ropes)
{
	m_numOfRopes = ropes;
}

int Candy::getAmountOfRopes() const
{
	return m_numOfRopes;
}

void Candy::setCandyLost(bool candyLost)
{
	m_candyLost = candyLost;
}

bool Candy::isCandyLost() const
{
	return m_candyLost;
}

void Candy::setCandy2Rope(bool candyattached)
{
	m_candy2Rope = candyattached;
}

bool Candy::isCandy2Rope() const
{
	return m_candy2Rope;
}

void Candy::setCandyGravity(bool Gravity)
{
	m_candyGravity = Gravity;
}

bool Candy::isCandyGravity() const
{
	return m_candyGravity;
}