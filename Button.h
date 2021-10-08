//
// Created by mohamed on 9/8/21.
//

#ifndef SORTING_VISUALIZER_BUTTON_H
#define SORTING_VISUALIZER_BUTTON_H


#include "global.h"

class Button {
private:
    sf::Sprite sprite;
    sf::Texture tx;

    float width;
    float height;
    float pos_x;
    float pos_y;
    std::string image;

public:
    Button(int pos_x, int pos_y, std::string image);

    bool isPointed(sf::Vector2i curser_position);

    void addImage();

    void set_green();

    void set_white();

    void set_scale(float x, float y);

    void set_color(sf::Color cl);

    void draw();

    float getWidth();

    float getHeight();

    float get_x();

    float get_y();
};


#endif //SORTING_VISUALIZER_BUTTON_H
