#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

#include "global.h"
#include "progressBar.h"
#include "Button.h"


int x;
vector<pair<int, int>> heights; // height, index
vector<sf::RectangleShape> columns;

void initialize_columns(); // give columns initial values initialize

void selection_sort();

void bubble_sort();

void merge_sort();

void quick_sort(int, int);

void insertion_sort();

void draw_all();

Button bubble(0, 0, "Resources/bubble.png");
Button selection(130, 0, "Resources/selection.png");
Button merge_(260, 0, "Resources/merge.png");
Button quick(390, 0, "Resources/quick.png");
Button insertion(520, 0, "Resources/insertion.png");

progressBar numberOfColumns(215, 15, 660, 20);
progressBar sort_speed(215, 15, 660, 55);

Button columns_number(640, -12, "Resources/columns.png");
Button speed_value(640, 25, "Resources/speed.png");


int main() {
    window.setPosition(sf::Vector2i(400, 70));
    srand(time(0));
    initialize_columns();

    columns_number.set_scale(2.3, 2.3);
    columns_number.set_color(sf::Color(37, 42, 52));

    speed_value.set_scale(2.3, 2.3);
    speed_value.set_color(sf::Color(37, 42, 52));

    sf::Event ev;
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == ev.Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and ev.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            if (bubble.isPointed(pos))
                bubble_sort();

            else if (selection.isPointed(pos))
                selection_sort();

            else if (merge_.isPointed(pos))
                merge_sort();

            else if (quick.isPointed(pos))
                initialize_columns(), quick_sort(0, N - 1);

            else if (insertion.isPointed(pos))
                insertion_sort();
        }

        if (sf::Mouse::Wheel::HorizontalWheel   // check wheel on progress bars
            && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            if (numberOfColumns.isPointed(pos)) {
                numberOfColumns.setProgress(pos.x);
                initialize_columns();
            } else if (sort_speed.isPointed(pos))
                sort_speed.setProgress(pos.x);
        }

        draw_all();
    }
    return 0;
}

void initialize_columns() {
    heights.clear();
    columns.clear();
    N = numberOfColumns.getProgress_high();
    if (N < 2)
        N = 2;
    SPEED = sf::microseconds(sort_speed.getProgress_low());
    heights = vector<pair<int, int>>(N); // height, index
    columns = vector<sf::RectangleShape>(N);
    for (char i = 0; i < N; ++i) {
        x = rand() % 30;
        x++;
        columns[i].setSize(sf::Vector2f(WIDTH / N, float(char(x)) * 16.17658));
        columns[i].setPosition(i * WIDTH / N, HEIGHT - columns[i].getSize().y);
        columns[i].setFillColor(sf::Color(37, 42, 52));
        columns[i].setOutlineThickness(0.7);
        heights[i] = {columns[i].getSize().y, i};
    }
}

void draw_all() {
    for (char i = 0; i < N; ++i)
        window.draw(columns[i]);

    bubble.draw();
    selection.draw();
    merge_.draw();
    quick.draw();
    insertion.draw();
    numberOfColumns.draw();
    sort_speed.draw();
    columns_number.draw();
    speed_value.draw();
    window.display();    // swap buffers
    window.clear(sf::Color(234, 234, 234));
}


void drawColumns(int left, int right) {
    sf::Clock clock;
    sf::RectangleShape &pivot = columns[left];
    sf::RectangleShape &small = columns[right];

    float new_small_x = pivot.getPosition().x;
    while (small.getPosition().x > new_small_x) { // swap the two columns
        pivot.move(0.01f, 0.0f);
        small.move(-0.01f, 0.0f);

        if (clock.getElapsedTime() >= SPEED) {
            for (char i = 0; i < N; ++i)
                window.draw(columns[i]);
            small.setFillColor(sf::Color(251, 54, 64));
            pivot.setFillColor(sf::Color::Cyan);

            window.draw(pivot);
            window.draw(small);
            window.display(); // swap buffers
            window.clear(sf::Color(234, 234, 234));
            clock.restart();

        }
    }
    small.setFillColor(sf::Color(37, 42, 52));
    pivot.setFillColor(sf::Color(37, 42, 52));
}

void bubble_sort() {
    initialize_columns();
    int i, j;
    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < N - i - 1; j++) {
            if (heights[j].first > heights[j + 1].first) {
                drawColumns(heights[j].second, heights[j + 1].second);
                // swap
                swap(heights[j], heights[j + 1]);

            } else
                continue;
        }
    }
}

void selection_sort() {
    initialize_columns();
    for (int step = 0; step < N - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < N; i++) {
            if (heights[i].first < heights[min_idx].first)
                min_idx = i;
        }
        drawColumns(heights[step].second, heights[min_idx].second); // left, right
        swap(heights[min_idx], heights[step]);
    }
}

void custom_selection_sort(int st, int en) {
    if (en >= N)
        en = N - 1;
    for (; st <= en - 1; st++) {
        int min_idx = st;
        for (int i = st + 1; i <= en; i++) {
            if (heights[i].first < heights[min_idx].first)
                min_idx = i;
        }
        drawColumns(heights[st].second, heights[min_idx].second); // left, right
        swap(heights[min_idx], heights[st]);
    }
}

void merge_sort() {
    initialize_columns();

    int step = 1;
    int ss = 0, ee = step;
    while (step <= N) {
        while (ss <= N) {
            custom_selection_sort(ss, ee);
            ss = ee + 1;
            ee = ss + step;
        }
        ss = 0;
        step = step * 2 + 1;
        ee = ss + step;
    }
    custom_selection_sort(0, N);
}

void custom_draw_columns(int left, int right, int pivot) { // for quick sort
    sf::Clock clock;
    sf::RectangleShape &large = columns[left];
    sf::RectangleShape &small = columns[right];

    float new_small_x = large.getPosition().x;
    while (small.getPosition().x > new_small_x) {
        large.move(0.01f, 0.0f);
        small.move(-0.01f, 0.0f);

        if (clock.getElapsedTime() >= SPEED) {
            for (char i = 0; i < N; ++i)
                window.draw(columns[i]);
            small.setFillColor(sf::Color(251, 54, 64)); // magenta
            large.setFillColor(sf::Color::Cyan); // Cyan
            columns[pivot].setFillColor(sf::Color::Green); // Cyan

            window.draw(large);
            window.draw(small);
            window.draw(columns[pivot]);

            window.display(); // swap buffers
            window.clear(sf::Color(234, 234, 234)); // White
            clock.restart();
        }
    }

    small.setFillColor(sf::Color(37, 42, 52));
    large.setFillColor(sf::Color(37, 42, 52));
    columns[pivot].setFillColor(sf::Color(37, 42, 52));

}

int partition(int first, int last) {
    int pivot_value = heights[first].first; // pivot --> first element
    int left_mark = first + 1;
    int right_mark = last;
    bool done = false;
    while (!done) {
        while (heights[left_mark].first <= pivot_value
               && left_mark <= right_mark)
            left_mark++;

        while (heights[right_mark].first >= pivot_value
               && right_mark >= left_mark)
            right_mark--;

        if (right_mark < left_mark)
            done = true;
        else {
            // graphics
            custom_draw_columns(heights[left_mark].second,
                                heights[right_mark].second, heights[first].second);
            swap(heights[left_mark], heights[right_mark]);
        }
    }
    // graphics
    drawColumns(heights[first].second, heights[right_mark].second);
    swap(heights[first], heights[right_mark]);
    return right_mark;
}

void quick_sort(int low = 0, int high = N - 1) {
    if (low < high) {
        int split = partition(low, high);
        quick_sort(low, split - 1);
        quick_sort(split + 1, high);
    }
}

void insertion_sort() {
    initialize_columns();
    int position;
    for (int i = 1; i < N; ++i) {
        position = i;
        while (position > 0
               and heights[position - 1].first > heights[position].first) {
            drawColumns(heights[position - 1].second, heights[position].second);
            swap(heights[position], heights[position - 1]);
            position--;
        }
    }
}

