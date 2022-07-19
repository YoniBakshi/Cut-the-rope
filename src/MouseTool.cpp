#include "MouseTool.h"
#include <sfml/Graphics/Shape.hpp>

MouseTool::MouseTool()
{
	m_MouseMarker.setRadius(5);
	m_MouseMarker.setOrigin(m_MouseMarker.getGlobalBounds().width / 2, m_MouseMarker.getGlobalBounds().height / 2);
	m_MouseMarker.setFillColor(sf::Color::Cyan);
}

MouseTool::~MouseTool()
{
}

// Get Mouse Pos : This will be used to get the position of mouse. 
sf::Vector2f MouseTool::getMousePos(sf::RenderWindow& window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	m_MousePos = window.mapPixelToCoords(pixelPos);

	return m_MousePos;
}

void MouseTool::eraseLine()
{
	m_lineCut.setSize({ 0, 0 });
	m_line.clear();
	m_lineCut.setOutlineColor(sf::Color::Transparent);
	m_lineCut.setFillColor(sf::Color::Transparent);
}

sf::VertexArray MouseTool::getLine() const
{
	return m_line;
}

// Update Mouse : This will be used to update the position of the mouse marker. 
void MouseTool::updateMouse(sf::RenderWindow& window)
{
	m_MouseMarker.setPosition(getMousePos(window));
}

// Draw Mouse Marker : This will be used to draw the marker on the screen. 
void MouseTool::drawMouseMarker(sf::RenderWindow& window, sf::Time deltaTime)
{
	updateMouse(window);
	window.draw(m_MouseMarker);
	window.draw(m_lineCut);

	m_elapsed += deltaTime;

	if (m_elapsed.asMilliseconds() < 30)
	{
		window.draw(m_lineCut);
	}
	else
	{
		m_lineCut.setSize({ INITIALIZE, INITIALIZE });	
		m_elapsed = m_elapsed.Zero;
	}

	if (m_line.getVertexCount() != NULL)
		window.draw(m_line);
}

// Create Line : This will be used to draw a line between the two defined points, where the mouse was clicked and released.
void MouseTool::CreateLine(sf::Vector2f cutStart, sf::Vector2f cutEnd)
{
	sf::RectangleShape line(sf::Vector2f(sqrt(pow(cutEnd.x - cutStart.x, 2) + pow(cutEnd.y - cutStart.y, 2)), 5));
	m_lineCut = line;
	m_lineCut.setPosition(sf::Vector2f(cutStart.x, cutStart.y));
	auto deg = atan2(cutEnd.y - cutStart.y, cutEnd.x - cutStart.x) * RADTODEG;
	m_lineCut.setRotation(deg);
	m_lineCut.setOutlineColor(sf::Color::Blue);

	m_cutStart = cutStart;
	m_cutEnd   = cutEnd;

	// Reset the line.
	m_line.clear();
	m_line.setPrimitiveType(sf::LineStrip);
	m_line.resize(2);

	// Define first point.
	m_line[0].position = cutStart;
	m_line[0].color	   = sf::Color::Transparent;

	// Define end point. 
	m_line[1].position = cutEnd;
	m_line[1].color    = sf::Color::Transparent;
}

// Line Intersect : This will be used to detect whether two lines defined by four points intersect.
bool MouseTool::lineIntersect(sf::Vector2f p2, sf::Vector2f p3)
{
	if (m_line.getVertexCount() > 0)
	{
		// Calculate all of the values 
		float l_A1 = m_cutEnd.y - m_cutStart.y;
		float l_B1 = m_cutStart.x - m_cutEnd.x;
		float l_C1 = l_A1 * m_cutStart.x + l_B1 * m_cutStart.y;
		float l_A2 = p3.y - p2.y;
		float l_B2 = p2.x - p3.x;
		float l_C2 = l_A2 * p2.x + l_B2 * p2.y;
		float l_fDenominator = l_A1 * l_B2 - l_A2 * l_B1;

		sf::Vector2f l_IntersectionPoint;

		// Find the intersection point. 
		if (l_fDenominator == 0)
			return false;		

		l_IntersectionPoint.x = (l_B2 * l_C1 - l_B1 * l_C2) / l_fDenominator;
		l_IntersectionPoint.y = (l_A1 * l_C2 - l_A2 * l_C1) / l_fDenominator;

		// Constrain check to line segments. 
		float l_rx0 = (l_IntersectionPoint.x - m_cutStart.x) / (m_cutEnd.x - m_cutStart.x);
		float l_ry0 = (l_IntersectionPoint.y - m_cutStart.y) / (m_cutEnd.y - m_cutStart.y);
		float l_rx1 = (l_IntersectionPoint.x - p2.x) / (p3.x - p2.x);
		float l_ry1 = (l_IntersectionPoint.y - p2.y) / (p3.y - p2.y);

		// Segments either intersect or they don't. 
		if (((l_rx0 >= 0 && l_rx0 <= 1) || (l_ry0 >= 0 && l_ry0 <= 1)) &&
			((l_rx1 >= 0 && l_rx1 <= 1) || (l_ry1 >= 0 && l_ry1 <= 1)))
		{
			m_line.clear();
			return true;
		}
		else
		{
			// std::cout << "Segment Intersect : False" << std::endl;
		}
	}

	return false;
}
