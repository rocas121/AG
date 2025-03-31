#include "bird.h"

Bird::Bird(sf::Vector2f size, sf::Vector2f pos, sf::Color color) : holdMouse(false), velocity(0.f, 0.f) {
	rect.setSize(size);
	rect.setFillColor(color);
	rect.setPosition(pos);
}



// FONCTION LANCE PIERRE
void Bird::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            holdMouse = true;
            mouseOffset = sf::Vector2f(sf::Mouse::getPosition(window)) - rect.getPosition();
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        holdMouse = false;
        rect.setFillColor(sf::Color::Green);

        sf::FloatRect rangeBounds(90, 490, 45, 45); //pos et taille de la range
        sf::Vector2f birdPos = rect.getPosition();

        
        // Check si Bird est hors range
        if (!rangeBounds.contains(birdPos)) {
            sf::Vector2f rangeCenter = { rangeBounds.left + rangeBounds.width / 2, rangeBounds.top + rangeBounds.height / 2 };

            //CALCULE 
            sf::Vector2f launchVelocity = rangeCenter - birdPos; // Vector from bird to center
            
            launchVelocity *= 10.0f; // += marche pas car c'est un sf::Vector2f donc *=

            velocity = launchVelocity; // 
        }
        else {
            rect.setPosition(100, 500); //pos reset si dans la range
        }
    }
}

void Bird::update(const sf::RenderWindow& window, sf::Time delta) {
    if (holdMouse) {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        rect.setPosition(mousePos - mouseOffset);
    }
    else {
        rect.move(velocity * delta.asSeconds()); // BOUGE LE BIRD, POUR LE MOMENT C TOUT DROIT
    }
}

void Bird::draw(sf::RenderWindow& window) const {
    window.draw(rect);
}