#pragma once
#include <SFML/Graphics.hpp>
#include "bird.h"

#include <iostream>

class Game {
public:
	Game() = default;
	int game();

private:
	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 600;


};
