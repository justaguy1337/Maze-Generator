#ifndef DRAWTEXT_H
#define DRAWTEXT_H

#include <string>

void draw_text(const bool &i_center_x, const bool &i_center_y, const int &i_x, const int &i_y, const std::string &i_text, sf::RenderWindow &i_window, const sf::Texture &i_font_texture, const sf::Color &i_color = sf::Color(255, 255, 255));

#endif