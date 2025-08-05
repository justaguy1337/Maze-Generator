#ifndef GLOBAL_H
#define GLOBAL_H

using namespace std;

namespace gbl
{
    namespace CELL
    {
        constexpr int SIZE = 4;

        namespace COLORS
        {
            const sf::Color GENERATION_PATH(0, 146, 255);
            const sf::Color DEFAULT(36, 36, 85);
            const sf::Color MAZE_PATH(255, 255, 255);
        }
    }

    namespace MAP
    {
        constexpr char BORDER_OFFSET = 2;
        constexpr char STEPS_PER_FRAME = 16;
        constexpr int COLUMNS = 158;
        constexpr int ROWS = 80;
    }

    namespace SCREEN
    {
        constexpr char RESIZE = 2;
        constexpr int HEIGHT = 360;
        constexpr int WIDTH = 640;

        constexpr chrono::microseconds FRAME_DURATION(16667);
    }

    template <typename i_value_type>
    using Vector2D = vector<vector<i_value_type>>;
}

#endif