#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Bird {
public:
    Bird(sf::Vector2f size, sf::Vector2f pos, sf::Color color);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void update(const sf::RenderWindow& window, sf::Time delta);
    void draw(sf::RenderWindow& window) const;
    void toggleFriction();
    void resetBird();

private:
    const float m = 0.8f;            // Masse de l'oiseau (kg)
    const float g = 9.81f * 20.0f;   // Constante gravitationnelle (m/s2), scaled for pixels (réduite)
    const float k = 10.0f;           // Constante de raideur du ressort (N/m)
    const float f2 = 0.2f / m;    // Coeff de frottement divisé par la masse (0.2/m)
    const float cr = 0.5f;           // Coefficient of restitution (for bounces)

    float calculateInitialVelocity(float alpha, float l1);
    void calculateTrajectory();

    sf::RectangleShape rect;
    sf::Vector2f velocity;
    sf::Vector2f initialPos;
    sf::Vector2f mouseOffset;
    std::vector<sf::Vector2f> trajectory;
    sf::Clock flightTimer;

    bool holdMouse;
    bool showTrajectory;
    bool useFriction;
    bool isLaunched;
};

#endif