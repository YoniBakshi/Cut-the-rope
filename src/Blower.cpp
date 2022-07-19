#include "Blower.h"

Blower::Blower(const sf::Vector2f pos,const int angle) : Blower()
{
	m_sprite.setPosition(pos.x,pos.y);
	m_sprite.setRotation(-angle);
	m_angle = angle;

	if (angle % 180 == 0)
		m_angle += 90;
	else if (angle == 90 || angle == 270)
		m_angle -= 90;
	else if (angle == 135 || angle == 315)
		m_angle += 180;

	m_blowZone.setSize({ PIC_SIZE/1.5,PIC_SIZE * 4 });
	m_blowZone.setOrigin(m_blowZone.getGlobalBounds().width-33, m_blowZone.getGlobalBounds().height+35);
	m_blowZone.setRotation(m_angle);
	m_angle = angle;
	m_blowZone.setPosition(pos);
}

Blower::Blower()
	: m_animation(Resources::instance().animationData((int)Resources::Object::o_Blower), m_sprite), 
	  m_angle(INITIALIZE)
{
	m_sprite.setTexture(Resources::instance().getTexture(Resources::Textures::t_Blower));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_animation.action(Action::A_Static);
}

Blower::~Blower()
{
}

void Blower::setAction(bool isClick)
{
	if(isClick)
		m_animation.action(Action::A_Blowing);
	else if(m_animation.animationEnded())
		m_animation.action(Action::A_Static);
}

sf::RectangleShape Blower::getBlowZone() const
{
	return m_blowZone;
}

float Blower::getAngle() const
{
	return m_angle;
}

void Blower::update(sf::Time deltaTime)
{
	m_animation.update(deltaTime);
}