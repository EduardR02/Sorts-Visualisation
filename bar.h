#pragma once
#include <SFML/Graphics.hpp>

class Rectangle {
        int height, posy, border_thickness, sort_id;
        double width, posx;
        std::unique_ptr<sf::RectangleShape> rect;
        static std::unique_ptr<sf::Color> selected_color, sorted_color, color, outline_color;
        void setup_rect(const sf::Color&, const sf::Color&);
        void set_color(sf::Color&);
        void set_outline_color(sf::Color&);
    public:
        Rectangle(double, int, double, int, int, int);
        Rectangle(const Rectangle& copy_rect);
        double get_width() const {
            return width;
        };
        int get_height() const {
            return height;
        };
        double get_posx() const{
            return posx;
        };
        int get_posy() const{
            return posy;
        };
        int get_border_thickness() const{
            return border_thickness;
        };
        int get_sort_id() const{
            return sort_id;
        }
        void set_posx(double);
        void set_posy(int);
        
        void highlight();
        void un_highlight();
        void highlight_sorted();
        sf::RectangleShape* const get_rect() const {
            return rect.get();
        };
};