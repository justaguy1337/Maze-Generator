#ifndef CELL_H
#define CELL_H

class Cell
{
private:
    bool checked;
    bool wall_bottom;
    bool wall_left;
    bool wall_right;
    bool wall_top;

    int x;
    int y;

    sf::Color color;

public:
    Cell(const int &i_x, const int &i_y);

    // getter functions

    bool get_checked() const;
    bool get_wall_bottom() const;
    bool get_wall_left() const;
    bool get_wall_right() const;
    bool get_wall_top() const;

    int get_x() const;
    int get_y() const;

    // setter functions

    void set_checked(const bool &i_value);
    void set_color(const sf::Color &i_value);
    void set_wall_bottom(const bool &i_value);
    void set_wall_left(const bool &i_value);
    void set_wall_right(const bool &i_value);
    void set_wall_top(const bool &i_value);

    sf::Color get_color() const;
};

#endif