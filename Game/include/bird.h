#pragma once
#include <SFML/Graphics.hpp>

class Bird {
	private:
		sf::RectangleShape rect;
		bool holdMouse;
		sf::Vector2f mouseOffset; //decalage souris
		sf::Vector2f velocity;

	public :
        Bird(sf::Vector2f size, sf::Vector2f pos, sf::Color color);

        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
        void update(const sf::RenderWindow& window, sf::Time delta);
        void draw(sf::RenderWindow& window) const;
};