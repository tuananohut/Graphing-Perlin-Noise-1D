#include <random>
#include "Shape.h"
#include <chrono>
#include <algorithm>
#include <iostream>

typedef struct
{
	float x, y;
} vector2;

vector2 randomGradient(int ix, int iy);
float dotGridGradient(int ix, int iy, float x, float y);
float interpolate(float a0, float a1, float w);
float perlin(float x, float y);

vector2 randomGradient(int ix, int iy)
{
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2;
	unsigned a = ix, b = iy;
	a *= 3284157443;

	b ^= a << s | a >> w - s;
	b *= 1911520717;

	a ^= b << s | b >> w - s;
	a *= 2048419325;
	float random = a * (3.14159265 / ~(~0u >> 1));

	vector2 v;
	v.x = sin(random);
	v.y = cos(random);

	return v;
}


float dotGridGradient(int ix, int iy, float x, float y)
{
	vector2 gradient = randomGradient(ix, iy);

	float dx = x - (float)ix;
	float dy = y - (float)iy;

	return (dx * gradient.x + dy * gradient.y);
}

float interpolate(float a0, float a1, float w)
{
	return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float perlin(float x, float y)
{
	int x0 = (int)x;
	int y0 = (int)y;

	int x1 = x0 + 1;
	int y1 = y0 + 1;

	float sx = x - (float)x0;
	float sy = y - (float)y0;

	float n0 = dotGridGradient(x0, y0, x, y);
	float n1 = dotGridGradient(x1, y0, x, y);
	float ix0 = interpolate(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	float ix1 = interpolate(n0, n1, sx);

	float value = interpolate(ix0, ix1, sy);

	return value;
}

int main()
{
	const int windowWidth = 1280;
	const int windowHeight = 800;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 10;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Graphing Perlin Noise", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	sf::VertexArray graph(sf::LineStrip, windowWidth);
	 
	float start = 0.0f;
	float offsetX = perlin(start * 0.1f, 0) * 200.0f;
	float inc = 0.01f;
	float xoff = 0.01f;

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}

		}
		
		window.clear(sf::Color(103, 114, 157));
		
		xoff = start;

		for (int x = 0; x < windowWidth; x++)
		{
			float n = perlin(x * xoff * 0.0005f, xoff * 0.01f) * windowHeight / 2 ;
			float wave = perlin(x * 0.01f, xoff * 0.02f) * 50.0f;
			float y = windowHeight / 2 + n + wave;

			graph[x].position = sf::Vector2f(x, y);
			graph[x].color = sf::Color(254, 217, 237);
			
			xoff += inc;
		}

		start += inc;

		if (start > windowWidth) 
		{
			start = 0.0f;
		}

		window.draw(graph);

		window.display();	
	}
	
	return 0;
}

