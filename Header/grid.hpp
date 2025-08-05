#ifndef GRID_H
#define GRID_H

using namespace std;

class Grid
{

private:
    int maze_2_counter;
    int maze_3_counter;

    stack<Cell *> maze_0_stack;

    vector<Cell *> maze_1_stack;
    vector<Cell *> maze_2_stack;

    sf::Sprite cell_sprite;
    sf::Texture cell_texture;

    gbl::Vector2D<Cell> maze_0_map;
    gbl::Vector2D<Cell> maze_1_map;
    gbl::Vector2D<Cell> maze_2_map;
    gbl::Vector2D<Cell> maze_3_map;

    Cell *maze_3_current_cell;

    RandomManager *random_manager;

public:
    Grid(RandomManager &i_random_manager);

    bool contains(const int &i_cell_x, const int &i_cell_y) const;

    void set_cells_connection(const bool &i_value, Cell &i_cell_0, Cell &i_cell_1);
    void draw(const char &i_maze_index, const int &i_position_x, const int &i_position_y, sf::RenderWindow &i_window);
    void update_maze_generator(const char &i_maze_index, int &i_maze_steps, chrono::microseconds &maze_duration);

    vector<Cell *> get_available_neighbors(const bool &i_get_checked, const char &i_maze_index, const Cell &i_cell);
};

#endif