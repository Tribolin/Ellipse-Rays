#include "SFML/Graphics.hpp" 

#include "Ellipse.h"



int main() {
    
    sf::RenderWindow window(sf::VideoMode(900, 900), "Art!",sf::Style::Fullscreen);
    
    Ellipse el;
    std::vector<sf::Vertex> Map;

    int a = window.getSize().x / 3;
    float b = a * 0.75f;
    
    for (auto& i : el.generateLine(a,b,0.1))
    {
        sf::Vector2f position = sf::Vector2f(i.x, i.y ) + sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
        Map.push_back(sf::Vertex(position, sf::Color::White, sf::Vector2f(250, 250)));
    }
   
   
    window.setFramerateLimit(30);


     float counter = -a ;
     float angleGive = 0;
    while (window.isOpen())
    {
        if (counter < a)
        {
            counter+= 1;
            
        }
        else
        {
            counter = -a;
            angleGive++;
        }

        //Roatating Vector
        double angle = ((int)angleGive % 10) * (PI / 10);
        double x =  cos(angle) + (sin(angle) * -1);
        double y  = cos(angle) + sin(angle);
        

        std::vector<Vec2> Rays = el.Raycast({ counter,0 },{x,y});
        std::vector<sf::Vertex> RayMap;
        for (auto& i : Rays)
        {
            sf::Vector2f position = sf::Vector2f(i.x, i.y) + sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
            RayMap.push_back(sf::Vertex(position, sf::Color::Red, sf::Vector2f(250, 250)));
            RayMap[0].color = sf::Color::Green;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
       
        window.clear();
        window.draw(&Map[0],Map.size(),sf::LinesStrip);
        window.draw(&RayMap[0], RayMap.size(), sf::LinesStrip);
        window.display();
    }

    return 0;
     return 0;
    }
   