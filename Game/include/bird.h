#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Bird {
private:
    sf::RectangleShape rect;
    bool holdMouse;
    sf::Vector2f mouseOffset; //decalage souris
    sf::Vector2f velocity;

    const float m = 0.8f;       // masse de l'oiseau (kg)
    const float g = 9.81f * 40.0f;  // constante gravitationnelle (m/s2)
    const float k = 100.0f;     // constante de raideur du ressort (N/m)
    const float f2 = 0.2f / m;  // coeff de frottement divise par la masse
    const float cr = 0.85f;  // coeff de restitution (caoutchouc )

    // vitesse
    const float VELOCITY_FACTOR = 10.0f; 

    // Variables pour la trajectoire
    std::vector<sf::Vector2f> trajectory;
    bool showTrajectory;
    bool useFriction;
    bool isLaunched;
    sf::Vector2f initialPos;
    sf::Clock flightTimer;

    // Methodes privees pour le calcul de trajectoire
    float calculateInitialVelocity(float alpha, float l1);
    void calculateTrajectory();

public:
    Bird(sf::Vector2f size, sf::Vector2f pos, sf::Color color);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void update(const sf::RenderWindow& window, sf::Time delta);
    void draw(sf::RenderWindow& window) const;

    void toggleFriction();
    void resetBird();
    bool isHeld() const { return holdMouse; }
    bool hasLaunched() const { return isLaunched; }
};