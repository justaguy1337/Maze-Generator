#ifndef RANDOMMANAGER_H
#define RANDOMMANAGER_H

#include <cfloat>
#include <random>

class RandomManager
{

private:
    std::mt19937_64 random_engine;

public:
    RandomManager();

    double get_random(const double &i_value_max, const double &i_value_min);
    float get_random(const float &i_value_max, const float &i_value_min);
    int get_random(const int &i_value_max, const int &i_value_min);
};

#endif