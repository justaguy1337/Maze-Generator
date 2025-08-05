#include <SFML/Graphics.hpp>
#include <cmath>

void draw_text(const bool &i_center_x, const bool &i_center_y, const int &i_x, const int &i_y, const std::string &i_text, sf::RenderWindow &i_window, const sf::Texture &i_font_texture, const sf::Color &i_color)
{

	int character_x;
	int character_y;

	int character_height;
	int character_width;

	sf::Sprite font_sprite(i_font_texture);
	font_sprite.setColor(i_color);

	character_height = i_font_texture.getSize().y;
	character_width = i_font_texture.getSize().x / 96;

	if (1 == i_center_x)
	{
		character_x = static_cast<int>(round(i_x - 0.5f * character_width * i_text.substr(0, i_text.find_first_of('\n')).size()));
	}
	else
	{
		character_x = i_x;
	}

	if (1 == i_center_y)
	{
		character_y = static_cast<int>(round(i_y - 0.5f * character_height * (1 + std::count(i_text.begin(), i_text.end(), '\n'))));
	}
	else
	{
		character_y = i_y;
	}

	for (int a = 0; a < i_text.size(); a++)
	{
		if ('\n' == i_text[a])
		{
			character_y += character_height;

			if (1 == i_center_x)
			{
				character_x = static_cast<int>(round(i_x - 0.5f * character_width * i_text.substr(1 + a, i_text.find_first_of('\n', 1 + a) - 1 - a).size()));
			}
			else
			{
				character_x = i_x;
			}

			continue;
		}

		font_sprite.setPosition(character_x, character_y);
		font_sprite.setTextureRect(sf::IntRect(character_width * (i_text[a] - 32), 0, character_width, character_height));
		i_window.draw(font_sprite);

		character_x += character_width;
	}
}