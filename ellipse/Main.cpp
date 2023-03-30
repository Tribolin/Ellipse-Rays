
#include "Ellipse.h"



int main() {
    //Create window instance 
    sf::RenderWindow window(sf::VideoMode(900, 900), "Ellipse Rays!",sf::Style::Fullscreen);// Start in Fullsceen
    
    Ellipse ellipse;
    std::vector<sf::Vertex> Map;//Will store Points on the ellipse 

    //Get Window Size and calcualate ellipse parameters
    int a = window.getSize().x / 3;
    float b = a * 0.75f;
    
    //Generate the Ellipse and move it to middle of the window 
    for (auto& i : ellipse.generateLine(a,b,0.1))
    {
        sf::Vector2f position = sf::Vector2f(i.x, i.y ) + sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
        Map.push_back(sf::Vertex(position, sf::Color::White, sf::Vector2f(250, 250)));
    }
   
   
    window.setFramerateLimit(100);

    //Parameters for moving the start position and Rotation of the Ray
     float counter = -a ;
     float angleGive = 0;
     
    
    
    while (window.isOpen())
    {
        //change Ray start Parameters
        if (counter < a)
        {
            counter+= 1;
            
        }
        else
        {
            counter = -a;
            angleGive++;
        }

        double angle = ((int)angleGive % 10) * (PI / 10);
        double x =  cos(angle) + (sin(angle) * -1);
        double y  = cos(angle) + sin(angle);
        
        //Generate Ray and position it in the window
        std::vector<Vec2> Rays = ellipse.Raycast({ counter,0 },{x,y});
        std::vector<sf::Vertex> RayMap;
        for (auto& i : Rays)
        {
            sf::Vector2f position = sf::Vector2f(i.x, i.y) + sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
            RayMap.push_back(sf::Vertex(position, sf::Color::Cyan, sf::Vector2f(250, 250)));
            RayMap[0].color = sf::Color::Green;//change the starting position color of the Ray to Green
        }

        //check for user input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
            
                return 0;
  
            }
        }
       
        //draw elements in window
        window.clear();
        window.draw(&Map[0],Map.size(),sf::LinesStrip);
        window.draw(&RayMap[0], RayMap.size(), sf::LinesStrip);
        window.display();
    }

    return 0;
    
    }
   