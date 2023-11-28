#include "Shape.h"

Shape::Shape(int posX, int posY, int pointC, float radius)
	:m_posX(posX), m_posY(posY), m_pointC(pointC), m_radius(radius)
{
	m_shape = std::make_shared<sf::CircleShape>();
	m_shape->setPosition(this->m_posX, this->m_posY);
	m_shape->setRadius(this->m_radius);
	m_shape->setPointCount(this->m_pointC);
	m_shape->setOrigin(m_shape->getRadius(), m_shape->getRadius());
	m_shape->setFillColor(sf::Color::White);
}
