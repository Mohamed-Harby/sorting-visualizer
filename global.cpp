//
// Created by mohamed on 8/8/21.
//

#include "global.h"
const int WIDTH = 900;
const int HEIGHT = 650;
sf::Time SPEED = sf::microseconds(30);
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "", sf::Style::Close);

int N;
float scale = 0.15;
const int button_width = 810 / 4;
const int button_height = 289 / 4;