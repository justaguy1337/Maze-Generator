#include <chrono>
#include <random>
#include <stack>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

#include "cell.hpp"
#include "drawText.hpp"
#include "global.hpp"
#include "randomManager.hpp"
#include "grid.hpp"
#include "game.hpp"

Game::Game() : window(sf::VideoMode(gbl::SCREEN::RESIZE * gbl::SCREEN::WIDTH, gbl::SCREEN::RESIZE * gbl::SCREEN::HEIGHT), "Maze Generator", sf::Style::Close),
               grid(random_manager)
{
    has_focus = window.hasFocus();

    window.setView(sf::View(sf::FloatRect(0, 0, gbl::SCREEN::WIDTH, gbl::SCREEN::HEIGHT)));

    font_texture.loadFromFile("Images/Font8.png");
}

bool Game::is_open() const
{
    return window.isOpen();
}

void Game::draw()
{
    if (has_focus == true)
    {
        window.clear();

        int maze_width = gbl::CELL::SIZE * gbl::MAP::COLUMNS;
        int maze_height = gbl::CELL::SIZE * gbl::MAP::ROWS;

        int pos_x = (gbl::SCREEN::WIDTH - maze_width) / 2;
        int pos_y = (gbl::SCREEN::HEIGHT - maze_height) / 3;

        switch (current_algorithm)
        {
        case 0:
            grid.draw(0, pos_x, pos_y, window);
            draw_stats(maze_0_steps,
                       pos_x,
                       pos_y + maze_height + 10,
                       maze_0_duration);
            break;
        case 1:
            grid.draw(1, pos_x, pos_y, window);
            draw_stats(maze_1_steps,
                       pos_x,
                       pos_y + maze_height + 10,
                       maze_1_duration);
            break;
        case 2:
            grid.draw(2, pos_x, pos_y, window);
            draw_stats(maze_2_steps,
                       pos_x,
                       pos_y + maze_height + 10,
                       maze_2_duration);
            break;
        case 3:
            grid.draw(3, pos_x, pos_y, window);
            draw_stats(maze_3_steps,
                       pos_x,
                       pos_y + maze_height + 10,
                       maze_3_duration);
            break;
        }

        window.display();
    }
}

void Game::draw_stats(const int &i_steps, const int &i_x, const int &i_y,
                      const std::chrono::microseconds &i_duration)
{
    std::stringstream string_stream;
    string_stream << std::fixed << std::setprecision(2) << i_duration.count() / 1000.f;

    // Get algorithm name based on current_algorithm
    std::string algo_name;
    switch (current_algorithm)
    {
    case 0:
        algo_name = "Backtracking Algorithm";
        break;
    case 1:
        algo_name = "Randomized Prim's Algorithm";
        break;
    case 2:
        algo_name = "Wilson's Algorithm";
        break;
    case 3:
        algo_name = "Aldous-Broder Algorithm";
        break;
    default:
        break;
    }

    draw_text(0, 0, i_x, i_y,
              "Steps: " + std::to_string(i_steps) +
                  " - Time: " + string_stream.str() + "ms" +
                  " (" + algo_name + ")", // Added algorithm name
              window, font_texture);
}

void Game::handle_events()
{
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Num1)
            {
                current_algorithm = 0;
            }
            else if (event.key.code == sf::Keyboard::Num2)
            {
                current_algorithm = 1;
            }
            else if (event.key.code == sf::Keyboard::Num3)
            {
                current_algorithm = 2;
            }
            else if (event.key.code == sf::Keyboard::Num4)
            {
                current_algorithm = 3;
            }
            break;

        default:
            break;
        }
    }
}

void Game::update()
{

    for (char a = 0; a < gbl::MAP::STEPS_PER_FRAME; a++)
    {
        switch (current_algorithm)
        {
        case 0:
            grid.update_maze_generator(0, maze_0_steps, maze_0_duration);
            break;
        case 1:
            grid.update_maze_generator(1, maze_1_steps, maze_1_duration);
            break;
        case 2:
            grid.update_maze_generator(2, maze_2_steps, maze_2_duration);
            break;
        case 3:
            grid.update_maze_generator(3, maze_3_steps, maze_3_duration);
            break;

        default:
            break;
        }
    }
}
