#include "game.h"

int Game::game() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Angry Birds-like", sf::Style::Titlebar | sf::Style::Close);
    sf::Clock clock;
    window.setFramerateLimit(60);
    
    Bird bird({ 25.f, 25.f }, { 100.f, 500.f }, sf::Color::Green);

    //AFFICHAGE DE LA RANGE POUR TIRRER
    sf::RectangleShape range(sf::Vector2f(45,45));
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



        window.clear();

        window.draw(range);
        bird.draw(window);
        
        window.display();
    }
    return 0;
}
