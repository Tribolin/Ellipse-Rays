#pragma once
#include "SFML/Graphics.hpp" 
#include "Vec2.h"
#include <vector>
class Window
{
public:
	Window();
	~Window();
	void Update()
	{
		//Get Inputs from User
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Update the Window
		window.clear();
		drawLines();
		window.display();
	}
	void MoveAndAddLine(std::vector<sf::Vector2f> Lines, sf::Color Color,bool MoveCenter);
private:
	sf::RenderWindow window;
	std::vector<std::vector<sf::Vertex>> LineMaps; //contains all the Points to draw as a Line
	void drawLines();

};

