#include"Frog.h"

Frog::Frog(const sf::Vector2f pos) : Frog()
{
	m_sprite.setPosition(pos);
	m_frogZone.setSize({ PIC_SIZE * 4, PIC_SIZE * 4 });			// Symbolize candy is in the area so setAction
	m_frogZone.setOrigin(m_frogZone.getGlobalBounds().width - PIC_SIZE * 2, m_frogZone.getGlobalBounds().height - PIC_SIZE * 2);
	m_frogZone.setPosition(pos);
}

Frog::Frog() 
	 : m_animation(Resources::instance().animationData((int)Resources::Object::o_Frog), m_sprite),
	   m_win(false), m_action(INITIALIZE_INT)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_Frog));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_animation.action(Action::A_Waiting);
}

Frog::~Frog()
{
}

void Frog::setWin(bool isWin)
{
	m_win = isWin;
}

bool Frog::getWin() const
{
	return m_win;
}

void Frog::setAction(int action)
{
	m_action = action;
	if (action == A_Almost)
		m_animation.action(Action::A_Almost);
	else if(action == A_Waiting && m_animation.animationEnded())
		m_animation.action(Action::A_Waiting);
	else if (action == A_Win)
		m_animation.action(Action::A_Win);
	else if (action == A_Lose)
		m_animation.action(Action::A_Lose);
}

bool Frog::getEnded() const
{
	return m_animation.animationEnded();
}

void Frog::update(sf::Time deltaTime)
{
	m_animation.update(deltaTime);
}

sf::RectangleShape Frog::getFrogZone() const
{
	return m_frogZone;
}
