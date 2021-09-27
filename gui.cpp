#include "gui.h"

GUI::GUI(double bar_width, int bar_border_thickness, double height_growth,
         int starting_height, int height_gap, int sleep_ms, int updates_per_draw) {
    this->bar_width = bar_width;
    this->height_gap = height_gap;
    this->starting_height = starting_height;
    this->height_growth = height_growth;
    this->sleep_ms = sleep_ms;
    this->updates_per_draw = updates_per_draw;
    this->bar_border_thickness = bar_border_thickness;
    background_color = std::make_unique<sf::Color>(40, 44, 52);
    init_texts();
    make_gui(n_squared);
}

void GUI::fill_array(const Complexity& complexity) {
    if (rectangles.size() == complexity) return;
    rectangles.clear();
    for (int i = 0; i < complexity; i++) {
        rectangles.push_back(std::make_unique<Rectangle>(bar_width, std::round(starting_height + (height_growth * i)),
                (bar_width + bar_border_thickness) * i + bar_border_thickness, window_height, bar_border_thickness, i));
    }
}

void GUI::make_gui(const Complexity& complexity) {
    this->window_width = (bar_width + bar_border_thickness) * complexity + bar_border_thickness;
    this->window_height = starting_height + height_growth * (complexity - 1) + height_gap;
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_width, window_height),
                                                     "Sort Visualisation", sf::Style::Default);
    fill_array(complexity);
}

void GUI::do_all_sorts() {
    Sorts* my_sorts = new Sorts(rectangles, sleep_ms, updates_per_draw);
    while (true) {
        do_sort(SortNames::bubble_sort, Complexity::n_squared, my_sorts);
        do_sort(SortNames::selection_sort, Complexity::n_squared, my_sorts);
        do_sort(SortNames::insertion_sort, Complexity::n_squared, my_sorts);
        do_sort(SortNames::cocktail_sort, Complexity::n_squared, my_sorts);
        do_sort(SortNames::gnome_sort, Complexity::n_squared, my_sorts);
        do_sort(SortNames::pancake_sort, Complexity::n_squared, my_sorts);
        do_sort(SortNames::shell_sort, Complexity::shell_cmplx, my_sorts);
        do_sort(SortNames::quick_sort, Complexity::n_logn, my_sorts);
        do_sort(SortNames::merge_sort, Complexity::n_logn, my_sorts);
        do_sort(SortNames::stooge_sort, Complexity::stooge_cmplx, my_sorts);
        do_sort(SortNames::bogo_sort, Complexity::bogo_cmplx, my_sorts);
    }
    delete my_sorts;
}

void GUI::do_single_sort(const SortNames& sort_name, const Complexity& complexity) {
    Sorts* my_sorts = new Sorts(rectangles, sleep_ms, updates_per_draw);
    do_sort(sort_name, complexity, my_sorts);
    delete my_sorts;
}

void GUI::do_sort(const SortNames& sort_name, const Complexity& complexity, Sorts* my_sorts) {
    change_arr_size(complexity);
    my_sorts->sorted = false;
    std::thread t1(&Sorts::do_sort, my_sorts, sort_name);
    while (window->isOpen() && !my_sorts->sorted) {
        handle_events(my_sorts);
        if (my_sorts->waiting) {
            draw_all(my_sorts, sort_name);
            my_sorts->waiting = false;
        }
        sf::sleep(sf::microseconds(sleep_ms*500));
    }
    t1.join();
}

void GUI::change_arr_size(const Complexity& complexity) {
    if (rectangles.size() == complexity) return;
    bar_width = (double)(window_width - (complexity + 1) * bar_border_thickness) / complexity;
    height_growth = (height_growth * rectangles.size()) / complexity;
    window_width = (bar_width + bar_border_thickness) * complexity + bar_border_thickness;
    window->setSize(sf::Vector2u(window_width, window_height));
    window->setView(sf::View(sf::FloatRect(0, 0, window_width, window_height)));
    fill_array(complexity);
}

void GUI::handle_events(Sorts* my_sorts) {
    sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                my_sorts->window_closed = true;
                window->close();
            }
        }
}

void GUI::draw_all_rectangles() {
    for (size_t i = 0; i < rectangles.size(); i++) {
        window->draw(*rectangles[i]->get_rect());
    }
}

void GUI::draw_text(Sorts* my_sorts, const SortNames& sort_name) {
    set_stats(my_sorts, sort_name);
    window->draw(*stat_text);
}

void GUI::draw_all(Sorts* my_sorts, const SortNames& sort_name) {
    window->clear(*background_color);
    draw_all_rectangles();
    draw_text(my_sorts, sort_name);
    window->display();
}

void GUI::init_texts() {
    stat_text = std::make_unique<sf::Text>();
    stat_font = std::make_unique<sf::Font>();
    if (!stat_font->loadFromFile("consola.ttf")) {
        std::cout << "Could not load font" << std::endl;
    }
    stat_text->setFont(*stat_font);
    stat_text->setFillColor(sf::Color::White);
    stat_text->setCharacterSize(20);
    stat_text->setStyle(sf::Text::Regular);
    stat_text->setPosition(20, 20);
}

void GUI::set_stats(Sorts* my_sorts, const SortNames& sort_name) {
    stat_text->setString(SortNamesArr[sort_name] + ", " + std::to_string(rectangles.size()) + " Elements\nSwaps:"
                         + std::to_string(my_sorts->get_swaps())
                         + "\nComparisons:" + std::to_string(my_sorts->get_comparisons()));
}
