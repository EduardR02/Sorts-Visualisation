#include "gui.h"

GUI::GUI(int window_width, int window_height, int bar_border_thickness,
         int starting_height, int height_gap, int sleep_ms, int updates_per_draw) {
    this->window_width = window_width;
    this->window_height = window_height;
    this->bar_border_thickness = bar_border_thickness;
    this->height_gap = height_gap;
    this->starting_height = starting_height;
    this->sleep_ms = sleep_ms;
    this->updates_per_draw = updates_per_draw;
    background_color = std::make_unique<sf::Color>(40, 44, 52);
    // does not make sense to init bar width and height growth here, as they are dependant on element amt.
    
    init_texts();
    make_gui(n_squared);
}

void GUI::fill_array(const Complexity& complexity) {
    if (rectangles.size() == complexity) return;
    rectangles.clear();
    // border does not count towards sfml rectangle origin coordinates, border goes beyond them.
    for (int i = 0; i < complexity; i++) {
        rectangles.push_back(std::make_unique<Rectangle>(bar_width, std::round(starting_height + (height_growth * i)),
                (bar_width + bar_border_thickness) * i + bar_border_thickness, window_height, bar_border_thickness, i));
    }
}

void GUI::make_gui(const Complexity& complexity) {
    bar_width = calc_bar_width(complexity);
    height_growth = calc_bar_height_growth(complexity);
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_width, window_height),
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
    bar_width = calc_bar_width(complexity);
    height_growth = calc_bar_height_growth(complexity);
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
    for (auto const& rect: rectangles) {
        window->draw(*rect->get_rect());
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

double GUI::calc_bar_width(const Complexity& complexity) {
    double new_width =  (double) (window_width - (complexity + 1) * bar_border_thickness) / (double) complexity;
    return new_width;
}

double GUI::calc_bar_height_growth(const Complexity& complexity) {
    return (double) (window_height - starting_height - height_gap) / (double) complexity;
}

double GUI::calc_adjusted_window_width(const Complexity& complexity) {
    return (bar_width + bar_border_thickness) * complexity + bar_border_thickness;
}