#include "GameObject.h"

GameObject::GameObject()
	: m_isDisposed(false), m_isClicked(false), m_ended(false)
{
}

GameObject::~GameObject()
{
}

void GameObject::drawObject(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

bool GameObject::isClicked() const
{
	return m_isClicked;
}

bool GameObject::isEnded() const
{
	return m_ended;
}

void GameObject::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

bool GameObject::checkShapeCollision(const sf::Shape& other) const
{
	return m_sprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

bool GameObject::checkCollision(const GameObject& candy, const GameObject& other) const
{
	return Collision::PixelPerfectTest(candy.m_sprite, other.m_sprite);
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

bool GameObject::checkContain(const sf::Vector2f& point) const
{
	return m_sprite.getGlobalBounds().contains(point);
}

sf::Vector2f GameObject::getObjPosition() const
{
	return m_sprite.getPosition();
}

void GameObject::setEnded(bool isEndeded)
{
	m_ended = isEndeded;
}

void GameObject::setClicked(bool isClicked)
{
	m_isClicked = isClicked;
}

bool GameObject::isDisposed() const
{
	return m_isDisposed;
}
void GameObject::setDisposed(bool isDisposed) { m_isDisposed = isDisposed; }
