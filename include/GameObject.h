#pragma once

#include "Macros.h"
#include "Collision.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void drawObject(sf::RenderWindow& window) const;
	void setPosition(sf::Vector2f pos);
	void setEnded(bool isEnded);
	void setDisposed(bool isDisposed);
	void setClicked(bool isClicked);
	bool isDisposed() const;
	bool isClicked() const;
	bool isEnded() const;
	bool checkContain(const sf::Vector2f& point) const;
	bool checkShapeCollision(const sf::Shape& other) const;
	bool checkCollision(const GameObject& pointCandy, const GameObject& pointOther) const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getObjPosition() const;

protected:
	sf::Sprite m_sprite;
	bool m_isDisposed;			// Is this object will be removed
	bool m_isClicked;
	bool m_ended;

private:
	
};

