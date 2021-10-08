//
// Created by mohamed on 9/8/21.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "progressBar.h"
#include "global.h"

progressBar::progressBar(float w, float h, float x, float y) :
        width(w), height(h), pos_x(x), pos_y(y), progress(w / 2) {
    progressBack.setSize({width, height});
    progressBack.setPosition({pos_x, pos_y});
    progressBack.setFillColor(sf::Color(255, 46, 99));

    progressFront.setSize({w / 2, height});
    progressFront.setPosition({pos_x, pos_y});
    progressFront.setFillColor(sf::Color(37, 42, 52));
}

void progressBar::setProgress(float progess) { // curser x value
    this->progress = progess;
    progressFront.setSize({progress - pos_x, height});
}

bool progressBar::isPointed(sf::Vector2i curser_position) {
    if (curser_position.x >= this->pos_x
        && curser_position.x <= this->pos_x + this->width
        && curser_position.y >= this->pos_y
        && curser_position.y <= this->pos_y + this->height) {
        return true;
    }
    return false;
}

void progressBar::draw() {
    window.draw(this->progressBack);
    window.draw(this->progressFront);
}

float progressBar::getWidth() {
    return width;
}

float progressBar::getHeight() {
    return height;
}

float progressBar::get_x() {
    return pos_x;
}

float progressBar::get_y() {
    return pos_y;
}

int progressBar::getProgress_high() {
    return progressFront.getSize().x / 3;
}

int progressBar::getProgress_low() {
    return progressFront.getSize().x / 6;
}

