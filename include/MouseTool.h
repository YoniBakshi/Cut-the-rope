//This will be used to cut the ropes within the game.This class will control the mouse functionality.

#pragma once

#include "Macros.h"
#include "GameObject.h"

class MouseTool : public GameObject
{
public:
	MouseTool();
	~MouseTool();

	void CreateLine(sf::Vector2f cutStart, sf::Vector2f cutEnd);
	void eraseLine();
	void updateMouse(sf::RenderWindow& window);
	void drawMouseMarker(sf::RenderWindow& window, sf::Time deltaTime);
	sf::VertexArray getLine() const;
	sf::Vector2f getMousePos(sf::RenderWindow& window);				// no const - update member mousepos

	// This will check to see if the line passed into the function intersects with the player defined line. 
	bool lineIntersect(sf::Vector2f p2, sf::Vector2f p3);

private:
	std::vector<sf::RectangleShape> theDrawing;

	// This will be used to show where the mouse currently is. 
	sf::CircleShape m_MouseMarker;
	sf::Vector2f	m_MousePos;
	sf::Vector2f	m_cutStart;
	sf::Vector2f	m_cutEnd;

	// This will display the line the player made. 
	sf::VertexArray m_line;
	sf::RectangleShape m_lineCut;

	sf::Time		m_elapsed = {};
};
