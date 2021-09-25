#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "bar.h"
#include <math.h>
#include <thread>
#include <array>
#include <string>
#include "my_enum.h"
#include "sorts.h"

class GUI {
        int bar_border_thickness, starting_height, height_gap, window_height, sleep_ms, updates_per_draw;
        double height_growth, window_width, bar_width;
        std::unique_ptr<sf::Color> background_color;
        std::vector<std::unique_ptr<Rectangle>> rectangles;
        std::unique_ptr<sf::RenderWindow> window;
        std::unique_ptr<sf::Text> stat_text;
        std::unique_ptr<sf::Font> stat_font;
    public:
        GUI(double, int, double, int, int, int, int);
        void make_gui(const Complexity& complexity);
        void do_all_sorts();
        void do_single_sort(const SortNames& sort_name, const Complexity& complexity);
    private:
        void draw_all(Sorts* my_sorts, const SortNames& sort_name);
        void init_texts();
        void set_stats(Sorts* my_sorts, const SortNames& sort_name);
        void draw_text(Sorts* my_sorts, const SortNames& sort_name);
        void fill_array(const Complexity& complexity);
        void draw_all_rectangles();
        void do_sort(const SortNames& sort_name, const Complexity& complexity, Sorts* my_sorts);
        void handle_events(Sorts* my_sorts);
        double get_ops(const std::string& complexity);
        void change_arr_size(const Complexity& comlexity);
};
