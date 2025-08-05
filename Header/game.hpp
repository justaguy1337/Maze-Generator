#ifndef GAME_H
#define GAME_H

using namespace std;

class Game
{

private:
    int maze_0_steps;
    int maze_1_steps;
    int maze_2_steps;
    int maze_3_steps;

    char active_algorithm; // 0-3 for the 4 algorithms, -1 for none
    bool algorithm_finished;
    bool has_focus;

    chrono::microseconds maze_0_duration;
    chrono::microseconds maze_1_duration;
    chrono::microseconds maze_2_duration;
    chrono::microseconds maze_3_duration;

    sf::Event event;

    sf::RenderWindow window;

    sf::Texture font_texture;

    RandomManager random_manager;

    Grid grid;

public:
    Game();

    bool is_open() const;

    void draw();
    void draw_stats(const int &i_steps, const int &i_w, const int &i_y, const chrono::microseconds &i_duration);
    void handle_events();
    void update();

private:
    int current_algorithm = 0;
};

#endif