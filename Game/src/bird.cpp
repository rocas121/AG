#include "bird.h"
#include <iostream>

Bird::Bird(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
    : holdMouse(false),
    velocity(0.f, 0.f),
    showTrajectory(true),
    useFriction(true),
    isLaunched(false),
    initialPos(pos) {
    rect.setSize(size);
    rect.setFillColor(color);
    rect.setPosition(pos);
}

float Bird::calculateInitialVelocity(float alpha, float l1) {
    float term1 = std::sqrt(k / m);
    float term2 = (m * g * std::sin(alpha)) / (k * l1);

    float v_eject = l1 * term1 * std::sqrt(1.0f - term2 * term2);

    // Scale the velocity for better in-game representation
    float scale_factor = 2.0f;
    return v_eject * scale_factor;
}

void Bird::calculateTrajectory() {
    // Efface la trajectoire precedente
    trajectory.clear();

    // Recupere la position actuelle et la position initiale pour calculer le vecteur de lancement
    sf::Vector2f birdPos = rect.getPosition();
    sf::Vector2f rangeCenter = { 90 + 45 / 2.0f, 490 + 45 / 2.0f };

    // Calcul du vecteur de lancement
    sf::Vector2f launchVector = rangeCenter - birdPos;
    float l1 = std::sqrt(launchVector.x * launchVector.x + launchVector.y * launchVector.y);

    // Inverser l'angle pour tenir compte de l'orientation des axes dans SFML
    float alpha = std::atan2(launchVector.y, launchVector.x);

    float v0 = calculateInitialVelocity(alpha, l1);

    float x = birdPos.x;
    float y = birdPos.y;
    float vx = v0 * std::cos(alpha);
    float vy = v0 * std::sin(alpha);

    trajectory.push_back(sf::Vector2f(x, y));

    const float dt = 0.01f;
    const int maxPoints = 500;

    for (int i = 0; i < maxPoints; i++) {
        // Mise à jour de la position
        x += vx * dt;
        y += vy * dt;

        // Mise à jour de la vitesse avec la formule appropriée
        vx += -f2 * vx * dt; // Friction horizontale
        vy += g * dt - f2 * vy * dt; // Gravité + friction verticale (g est positif car SFML a Y vers le bas)

        // Ajoute le point à la trajectoire
        trajectory.push_back(sf::Vector2f(x, y));

        // Arrête la simulation si l'oiseau touche le sol ou sort de l'ecran
        if (y > 600 || x > 800 || x < 0) break;
    }
}

void Bird::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            holdMouse = true;
            isLaunched = false;
            mouseOffset = sf::Vector2f(sf::Mouse::getPosition(window)) - rect.getPosition();
            rect.setFillColor(sf::Color::Yellow);  // Couleur Jaune quand l'oiseau est tenu
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && holdMouse) {
        holdMouse = false;
        rect.setFillColor(sf::Color::Green);

        sf::FloatRect rangeBounds(90, 490, 45, 45); //pos et taille de la range
        sf::Vector2f birdPos = rect.getPosition();

        // Check si Bird est hors range
        if (!rangeBounds.contains(birdPos)) {
            sf::Vector2f rangeCenter = { rangeBounds.left + rangeBounds.width / 2, rangeBounds.top + rangeBounds.height / 2 };

            // Calcul du vecteur de lancement
            sf::Vector2f launchVector = rangeCenter - birdPos;
            float l1 = std::sqrt(launchVector.x * launchVector.x + launchVector.y * launchVector.y);

            // Inverser l'angle pour tenir compte de l'orientation des axes dans SFML
            float alpha = std::atan2(launchVector.y, launchVector.x);

            float v0 = calculateInitialVelocity(alpha, l1);

            // Definition de la vitesse de l'oiseau
            velocity.x = v0 * std::cos(alpha);
            velocity.y = v0 * std::sin(alpha);

            // Calcul de la trajectoire predite
            calculateTrajectory();

            isLaunched = true;
            flightTimer.restart();

            // Debug
            std::cout << "Lancement - Distance: " << l1 << "px, Angle: " << alpha * 180 / 3.14159f
                << "°, Vitesse: " << v0 << " u/s" << std::endl;
        }
        else {
            resetBird();
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F) {
            toggleFriction();
        }
        else if (event.key.code == sf::Keyboard::R) {
            resetBird();
        }
        // Press Space to debug and show trajectory
        else if (event.key.code == sf::Keyboard::Space && !isLaunched && !holdMouse) {
            calculateTrajectory();
        }
    }

    // Mise à jour continue de la trajectoire prevue pendant le drag
    if (holdMouse) {
        calculateTrajectory();
    }
}

void Bird::update(const sf::RenderWindow& window, sf::Time delta) {
    if (holdMouse) {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        rect.setPosition(mousePos - mouseOffset);
    }
    else if (isLaunched) {
        float dt = delta.asSeconds();

        // Deplacement base sur la vitesse actuelle
        rect.move(velocity * dt);

        velocity.x += -f2 * velocity.x * dt; // Friction horizontale
        velocity.y += g * dt - f2 * velocity.y * dt; // Gravité + friction verticale

        if (rect.getPosition().y + 34 > 610) {
            velocity.y =  - velocity.y  * cr;
            rect.setPosition(rect.getPosition().x, 610 - 34); // Teleporte juste au dessus du sol
        }

        // Verification des collisions avec les bords
        if (rect.getPosition().x > 800 || rect.getPosition().x < 0) {
            resetBird();
        }
    }
}

void Bird::draw(sf::RenderWindow& window) const {
    // Afficher la trajectoire prevue
    if (trajectory.size() >= 2 && (holdMouse || !isLaunched)) {
        sf::VertexArray lines(sf::LinesStrip, trajectory.size());
        for (size_t i = 0; i < trajectory.size(); ++i) {
            lines[i].position = trajectory[i];
            lines[i].color = sf::Color::Red;
        }
        window.draw(lines);
    }

    // Afficher l'oiseau
    window.draw(rect);
}

void Bird::toggleFriction() {
    useFriction = !useFriction;

    std::cout << "Frottement: " << (useFriction ? "Active" : "Desactive") << std::endl;

    if (holdMouse || isLaunched) {
        calculateTrajectory();
    }
}

void Bird::resetBird() {
    rect.setPosition(initialPos);
    velocity = sf::Vector2f(0.f, 0.f);
    isLaunched = false;
    rect.setFillColor(sf::Color::Green);
}