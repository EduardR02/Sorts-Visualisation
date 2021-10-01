#include "bar.h"

std::unique_ptr<sf::Color> Rectangle::selected_color = std::make_unique<sf::Color>(97, 175, 239);
std::unique_ptr<sf::Color> Rectangle::sorted_color = std::make_unique<sf::Color>(152, 195, 121);
std::unique_ptr<sf::Color> Rectangle::color = std::make_unique<sf::Color>(224, 108, 117);
std::unique_ptr<sf::Color> Rectangle::outline_color = std::make_unique<sf::Color>(40, 44, 52);

Rectangle::Rectangle(double width, int height, double posx, int posy, int border_thickness, int sort_id) {
    this->width = width;
    this->height = height;
    this->posx = posx;
    this->posy = posy - height;
    this->border_thickness = border_thickness;
    this->sort_id = sort_id;
    setup_rect(*color, *outline_color);
}

Rectangle::Rectangle(const Rectangle& copy_rect) {
    this->width = copy_rect.width;
    this->height = copy_rect.height;
    this->posx = copy_rect.posx;
    this->posy = copy_rect.posy;
    this->border_thickness = copy_rect.border_thickness;
    this->sort_id = copy_rect.sort_id;
    setup_rect(copy_rect.rect->getFillColor(), copy_rect.rect->getOutlineColor());
}

void Rectangle::setup_rect(const sf::Color& color, const sf::Color& outline_color) {
    rect = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    rect->setPosition(posx, posy);
    rect->setFillColor(color);
    rect->setOutlineThickness(border_thickness);
    rect->setOutlineColor(outline_color);
}

void Rectangle::set_posx(double posx) {
    this->posx = posx;
    rect->setPosition(posx, posy);
}

void Rectangle::set_posy(int posy) {
    this->posy = posy;
    rect->setPosition(posx, posy - height);
}

void Rectangle::set_color(sf::Color& color) {
    rect->setFillColor(color);
}

void Rectangle::set_outline_color(sf::Color& outline_color) {
    rect->setOutlineColor(outline_color);
}

void Rectangle::highlight() {
    set_color(*selected_color);
}

void Rectangle::un_highlight() {
    set_color(*color);
}

void Rectangle::highlight_sorted() {
    set_color(*sorted_color);
}