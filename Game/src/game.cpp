#include "game.h"
#include <iostream>

int Game::game() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Angry Birds Physics", sf::Style::Titlebar | sf::Style::Close);
    sf::Clock clock;

    Bird bird({ 25.f, 25.f }, { 100.f, 500.f }, sf::Color::Green);

    //AFFICHAGE DE LA RANGE POUR TIRRER
    sf::RectangleShape range(sf::Vector2f(45, 45));
    range.setPosition(90, 490);
    range.setFillColor(sf::Color::White);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            bird.handleEvent(event, window);
        }

        sf::Time deltaTime = clock.restart();

        bird.update(window, deltaTime);

        window.clear(sf::Color(50, 50, 50));

        window.draw(range);
        bird.draw(window);

        window.display();
    }
    return 0;
}