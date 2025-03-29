#include "game.h"

void game() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Angry Birds-like", sf::Style::Titlebar | sf::Style::Close);
    
    sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(25.f, 550.f);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        //Mouvement rect
        sf::Time deltaTime = clock.restart();
        float movementSpeed = 100.f;
        shape.move(movementSpeed * deltaTime.asSeconds(), 0.f);

        window.clear();
        window.draw(shape);
        window.display();
    }
}