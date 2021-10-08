//
// Created by mohamed on 9/8/21.
//

#ifndef SORTING_VISUALIZER_PROGRESSBAR_H
#define SORTING_VISUALIZER_PROGRESSBAR_H

#include <SFML/Graphics.hpp>
#include "glob.h"

class progressBar {
private:
    sf::RectangleShape progressBack;
    sf::RectangleShape progressFront;
    float width;
    float height;
    float pos_x;
    float pos_y;
    float progress;
public:
    progressBar(float w, float h, float x, float y);

    void setProgress(float progess);

    bool isPointed(sf::Vector2i curser_position);

    void draw();

    float getWidth();

    float getHeight();

    float get_x();

    float get_y();

    int getProgress_high();

    int getProgress_low();

};


#endif //SORTING_VISUALIZER_PROGRESSBAR_H
