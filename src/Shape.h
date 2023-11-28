#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


class Shape
{
public:
	Shape(int posX, int posY, int pointC, float radius);

	std::shared_ptr<sf::CircleShape> m_shape;
private:
	int m_posX = 400, m_posY = 300;
	float m_radius = 300;
	int m_pointC = 100;
};