#include <chrono>
#include <random>
#include <stack>
#include <SFML/Graphics.hpp>

#include "cell.hpp"
#include "global.hpp"
#include "randomManager.hpp"
#include "grid.hpp"

Grid::Grid(RandomManager &i_random_manager) : maze_2_counter(1),
											  maze_3_counter(1),
											  cell_sprite(cell_texture),
											  maze_0_map(gbl::MAP::COLUMNS),
											  maze_1_map(gbl::MAP::COLUMNS),
											  maze_2_map(gbl::MAP::COLUMNS),
											  maze_3_map(gbl::MAP::COLUMNS),
											  random_manager(&i_random_manager)
{
	cell_texture.loadFromFile("Images/Cell" + std::to_string(gbl::CELL::SIZE) + ".png");

	// Initialize all cells in all mazes
	for (int a = 0; a < gbl::MAP::COLUMNS; a++)
		for (int b = 0; b < gbl::MAP::ROWS; b++)
		{
			maze_0_map[a].push_back(Cell(a, b));
			maze_1_map[a].push_back(Cell(a, b));
			maze_2_map[a].push_back(Cell(a, b));
			maze_3_map[a].push_back(Cell(a, b));
		}

	// Generate unique random starting positions for each algorithm
	int starts[4][2]; // Stores staring[x,y] for each algorithm's start

	// Algorithm 0 (Backtracker)
	starts[0][0] = random_manager->get_random(gbl::MAP::COLUMNS - 1, 0);
	starts[0][1] = random_manager->get_random(gbl::MAP::ROWS - 1, 0);

	// Algorithm 1 (Prim's) - ensure different from 0
	do
	{
		starts[1][0] = random_manager->get_random(gbl::MAP::COLUMNS - 1, 0);
		starts[1][1] = random_manager->get_random(gbl::MAP::ROWS - 1, 0);
	} while (starts[1][0] == starts[0][0] && starts[1][1] == starts[0][1]);

	// Algorithm 2 (Wilson's) - ensure different from 0 and 1
	do
	{
		starts[2][0] = random_manager->get_random(gbl::MAP::COLUMNS - 1, 0);
		starts[2][1] = random_manager->get_random(gbl::MAP::ROWS - 1, 0);
	} while ((starts[2][0] == starts[0][0] && starts[2][1] == starts[0][1]) ||
			 (starts[2][0] == starts[1][0] && starts[2][1] == starts[1][1]));

	// Algorithm 3 (Aldous-Broder) - ensure different from 0,1,2
	do
	{
		starts[3][0] = random_manager->get_random(gbl::MAP::COLUMNS - 1, 0);
		starts[3][1] = random_manager->get_random(gbl::MAP::ROWS - 1, 0);
	} while ((starts[3][0] == starts[0][0] && starts[3][1] == starts[0][1]) ||
			 (starts[3][0] == starts[1][0] && starts[3][1] == starts[1][1]) ||
			 (starts[3][0] == starts[2][0] && starts[3][1] == starts[2][1]));

	// Initialize Algorithm 0 (Backtracker)
	maze_0_stack.push(&maze_0_map[starts[0][0]][starts[0][1]]);
	maze_0_stack.top()->set_color(gbl::CELL::COLORS::GENERATION_PATH);
	maze_0_stack.top()->set_checked(true);

	// Initialize Algorithm 1 (Prim's)
	maze_1_stack.push_back(&maze_1_map[starts[1][0]][starts[1][1]]);
	maze_1_stack.back()->set_color(gbl::CELL::COLORS::GENERATION_PATH);
	maze_1_stack.back()->set_checked(true);

	// Initialize Algorithm 2 (Wilson's)
	maze_2_stack.push_back(&maze_2_map[starts[2][0]][starts[2][1]]);
	maze_2_stack.back()->set_color(gbl::CELL::COLORS::GENERATION_PATH);

	// For Wilson's mark a different random cell as part of the maze as it requires a
	// start and end point to form a maze
	int wilson_maze_x, wilson_maze_y;
	do
	{
		wilson_maze_x = random_manager->get_random(gbl::MAP::COLUMNS - 1, 0);
		wilson_maze_y = random_manager->get_random(gbl::MAP::ROWS - 1, 0);
	} while (wilson_maze_x == starts[2][0] && wilson_maze_y == starts[2][1]);

	maze_2_map[wilson_maze_x][wilson_maze_y].set_checked(true);
	maze_2_map[wilson_maze_x][wilson_maze_y].set_color(gbl::CELL::COLORS::MAZE_PATH);

	// Initialize Algorithm 3 (Aldous-Broder)
	maze_3_current_cell = &maze_3_map[starts[3][0]][starts[3][1]];
	maze_3_current_cell->set_checked(true);
	maze_3_current_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);
}

bool Grid::contains(const int &i_cell_x, const int &i_cell_y) const
{
	if (0 > i_cell_x || gbl::MAP::COLUMNS <= i_cell_x)
	{
		return false;
	}

	if (0 > i_cell_y || gbl::MAP::ROWS <= i_cell_y)
	{
		return false;
	}

	return true;
}

void Grid::set_cells_connection(const bool &i_value, Cell &i_cell_0, Cell &i_cell_1)
{
	if (1 < abs(i_cell_0.get_x() - i_cell_1.get_x()) || 1 < abs(i_cell_0.get_y() - i_cell_1.get_y()))
	{
		return;
	}

	if (i_cell_0.get_x() == i_cell_1.get_x() && i_cell_0.get_y() == i_cell_1.get_y())
	{
		return;
	}

	if (i_cell_0.get_x() != i_cell_1.get_x() && i_cell_0.get_y() != i_cell_1.get_y())
	{
		return;
	}

	if (i_cell_0.get_x() < i_cell_1.get_x())
	{
		i_cell_0.set_wall_right(i_value);
		i_cell_1.set_wall_left(i_value);
	}
	else if (i_cell_0.get_x() > i_cell_1.get_x())
	{
		i_cell_0.set_wall_left(i_value);
		i_cell_1.set_wall_right(i_value);
	}
	else if (i_cell_0.get_y() < i_cell_1.get_y())
	{
		i_cell_0.set_wall_bottom(i_value);
		i_cell_1.set_wall_top(i_value);
	}
	else if (i_cell_0.get_y() > i_cell_1.get_y())
	{
		i_cell_0.set_wall_top(i_value);
		i_cell_1.set_wall_bottom(i_value);
	}
}

void Grid::draw(const char &i_maze_index, const int &i_position_x, const int &i_position_y, sf::RenderWindow &i_window)
{
	gbl::Vector2D<Cell> *current_maze = &maze_0_map; // Backtracking Algorithm -> i_maze_index = 0

	if (i_maze_index == 1) // Prim's Algorithm
	{
		current_maze = &maze_1_map;
	}
	else if (i_maze_index == 2) // Wilson's Algorithm
	{
		current_maze = &maze_2_map;
	}
	else if (i_maze_index == 3) // Aldous-Broder Algorithm
	{
		current_maze = &maze_3_map;
	}

	for (int a = 0; a < gbl::MAP::COLUMNS; a++)
		for (int b = 0; b < gbl::MAP::ROWS; b++)
		{
			// Converting our 4 booleans into a decimal number from 0 to 15.
			char cell_state = (*current_maze)[a][b].get_wall_bottom() + 2 * (*current_maze)[a][b].get_wall_left() + 4 * (*current_maze)[a][b].get_wall_right() + 8 * (*current_maze)[a][b].get_wall_top();

			cell_sprite.setColor((*current_maze)[a][b].get_color());
			cell_sprite.setPosition(i_position_x + gbl::CELL::SIZE * a, i_position_y + gbl::CELL::SIZE * b);
			cell_sprite.setTextureRect(sf::IntRect(gbl::CELL::SIZE * cell_state, 0, gbl::CELL::SIZE, gbl::CELL::SIZE));

			i_window.draw(cell_sprite);
		}
}

void Grid::update_maze_generator(const char &i_maze_index, int &i_maze_steps, std::chrono::microseconds &maze_duration)
{
	if (i_maze_index == 0) // The Backtracking Algorithm
	{
		if (maze_0_stack.empty() == false)
		{
			std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

			std::vector<Cell *> neighbors;

			Cell *current_cell = maze_0_stack.top();

			neighbors = get_available_neighbors(false, i_maze_index, *current_cell);

			if (neighbors.empty())
			{
				// We're backtracking here.
				current_cell->set_color(gbl::CELL::COLORS::MAZE_PATH);
				maze_0_stack.pop();
			}
			else
			{
				Cell *next_cell = neighbors[random_manager->get_random(neighbors.size() - 1, 0)];

				current_cell->set_checked(true);
				next_cell->set_checked(true);
				next_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);

				set_cells_connection(false, *current_cell, *next_cell);

				maze_0_stack.push(next_cell);
			}

			i_maze_steps++;

			maze_duration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
		}
	}
	else if (i_maze_index == 1) // The Randomized Prim's Algorithm
	{
		if (maze_1_stack.empty() == false)
		{
			std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

			int current_cell_index = random_manager->get_random(maze_1_stack.size() - 1, 0);

			std::vector<Cell *> neighbors;

			Cell *current_cell;

			current_cell = maze_1_stack[current_cell_index];

			neighbors = get_available_neighbors(false, i_maze_index, *current_cell);

			if (neighbors.empty() == true)
			{
				current_cell->set_color(gbl::CELL::COLORS::MAZE_PATH);
				maze_1_stack.erase(current_cell_index + maze_1_stack.begin());
			}
			else
			{
				Cell *next_cell = neighbors[random_manager->get_random(neighbors.size() - 1, 0)];

				current_cell->set_checked(true);
				next_cell->set_checked(true);
				next_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);

				set_cells_connection(false, *current_cell, *next_cell);

				maze_1_stack.push_back(next_cell);
			}

			i_maze_steps++;

			maze_duration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
		}
	}
	else if (i_maze_index == 2) // Wilson's Algorithm
	{
		if (maze_2_stack.empty() == false)
		{
			std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

			std::vector<Cell *> neighbors;

			Cell *current_cell = maze_2_stack.back();
			Cell *next_cell;

			neighbors = get_available_neighbors(true, i_maze_index, *current_cell);

			do
			{
				next_cell = neighbors[random_manager->get_random(neighbors.size() - 1, 0)];
			} while (1 < maze_2_stack.size() && next_cell == maze_2_stack[maze_2_stack.size() - 2]); // Start random walk

			// We reached the cell that's part of our maze.
			if (next_cell->get_checked() == true)
			{
				// Making our generation path part of the maze.
				for (int a = 0; a < maze_2_stack.size(); a++)
				{
					maze_2_counter++;

					maze_2_stack[a]->set_checked(true);
					maze_2_stack[a]->set_color(gbl::CELL::COLORS::MAZE_PATH);
				}

				set_cells_connection(false, *current_cell, *next_cell);

				maze_2_stack.clear(); // clears stack

				// Starting a new generation path (if possible)
				if (maze_2_counter < gbl::MAP::COLUMNS * gbl::MAP::ROWS)
				{
					int random_cell_x;
					int random_cell_y;

					do
					{
						random_cell_x = random_manager->get_random(gbl::MAP::COLUMNS - 1, 0);
						random_cell_y = random_manager->get_random(gbl::MAP::ROWS - 1, 0);
					} while (1 == maze_2_map[random_cell_x][random_cell_y].get_checked());

					maze_2_stack.push_back(&maze_2_map[random_cell_x][random_cell_y]);
					maze_2_stack.back()->set_color(gbl::CELL::COLORS::GENERATION_PATH);
				}
			}
			else
			{
				bool loop = false;

				for (int a = 0; a < maze_2_stack.size() - 1; a++)
					if (maze_2_stack[a] == next_cell)
					{
						loop = true;

						// we are disconnecting the cells that are part of the loop
						for (int b = a + 1; b < maze_2_stack.size(); b++)
						{
							maze_2_stack[b]->set_color(gbl::CELL::COLORS::DEFAULT);

							set_cells_connection(true, *maze_2_stack[b - 1], *maze_2_stack[b]);
						}

						// deleting the loop cells
						maze_2_stack.erase(1 + a + maze_2_stack.begin(), maze_2_stack.end());

						break;
					}

				if (loop == false)
				{
					next_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);

					set_cells_connection(false, *current_cell, *next_cell);

					maze_2_stack.push_back(next_cell);
				}
			}

			i_maze_steps++;

			maze_duration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
		}
	}
	else if (i_maze_index == 3) // The Aldous-Broder Algorithm
	{
		if (maze_3_counter < gbl::MAP::COLUMNS * gbl::MAP::ROWS)
		{
			std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

			std::vector<Cell *> neighbors;

			Cell *next_cell;

			neighbors = get_available_neighbors(true, i_maze_index, *maze_3_current_cell);

			// Moving randomly.
			next_cell = neighbors[random_manager->get_random(neighbors.size() - 1, 0)];

			maze_3_current_cell->set_color(gbl::CELL::COLORS::MAZE_PATH);

			// Connecting the cells that haven't been checked yet.
			if (next_cell->get_checked() == false)
			{
				maze_3_counter++;

				set_cells_connection(false, *maze_3_current_cell, *next_cell);

				next_cell->set_checked(true);
			}

			maze_3_current_cell = next_cell;

			if (maze_3_counter == gbl::MAP::COLUMNS * gbl::MAP::ROWS)
			{
				next_cell->set_color(gbl::CELL::COLORS::MAZE_PATH);
			}
			else
			{
				next_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);
			}

			i_maze_steps++;

			maze_duration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
		}
	}
}

std::vector<Cell *> Grid::get_available_neighbors(const bool &i_get_checked, const char &i_maze_index, const Cell &i_cell)
{
	std::vector<Cell *> available_neighbors;

	gbl::Vector2D<Cell> *current_maze = &maze_0_map;

	if (i_maze_index == 1)
	{
		current_maze = &maze_1_map;
	}
	else if (i_maze_index == 2)
	{
		current_maze = &maze_2_map;
	}
	else if (i_maze_index == 3)
	{
		current_maze = &maze_3_map;
	}

	for (int a = 0; a < 4; a++)
	{
		int neighbor_x = i_cell.get_x() + (1 < a) - a % 2;
		int neighbor_y = i_cell.get_y() + (2 > a) - a % 2;

		if (contains(neighbor_x, neighbor_y) == false)
		{
			continue;
		}

		if (i_get_checked == false && (*current_maze)[neighbor_x][neighbor_y].get_checked() == true)
		{
			continue;
		}

		available_neighbors.push_back(&(*current_maze)[neighbor_x][neighbor_y]);
	}

	return available_neighbors;
}
