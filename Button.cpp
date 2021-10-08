//
// Created by mohamed on 9/8/21.
//

#include "Button.h"
#include "global.h"

#include <iostream>

void Button::addImage() {
    tx.loadFromFile(image);
    tx.setSmooth(true);
    sprite.setTexture(tx);
}


Button::Button(int pos_x, int pos_y, std::string filename) :
        width(button_width), height(button_height), pos_x(pos_x), pos_y(
        pos_y), image(filename) {
    this->sprite.scale({0.15, 0.15}); // {0.16, 0.16}

    this->sprite.setPosition(pos_x, pos_y);
    addImage();
}

void Button::set_scale(float x, float y) {
    this->sprite.scale({x, y}); // {0.16, 0.16}
}

void Button::set_color(sf::Color cl) {
    this->sprite.setColor(cl);
}

bool Button::isPointed(sf::Vector2i curser_position) {
    auto translated_pos = window.mapPixelToCoords(curser_position); // Mouse position translated into world coordinates
    if (sprite.getGlobalBounds().contains(translated_pos)) // Rectangle-contains-point check
        return true;
    return false;
}

void Button::set_green() {
    sprite.setColor(sf::Color::Green);
}

void Button::set_white() {
    sprite.setColor(sf::Color::White);
}

void Button::draw() {
    window.draw(this->sprite);
}

float Button::getWidth() {
    return width;
}

float Button::getHeight() {
    return height;
}

float Button::get_x() {
    return pos_x;
}

float Button::get_y() {
    return pos_y;
}


