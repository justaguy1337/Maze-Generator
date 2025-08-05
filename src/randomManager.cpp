#include <chrono>
#include <random>

#include "randomManager.hpp"

using namespace std;

RandomManager::RandomManager() : random_engine(chrono::system_clock::now().time_since_epoch().count())
{
}

double RandomManager::get_random(const double &i_value_max, const double &i_value_min)
{
	uniform_real_distribution<double> distribution(i_value_min, nextafter(i_value_max, DBL_MAX));

	return distribution(random_engine);
}

float RandomManager::get_random(const float &i_value_max, const float &i_value_min)
{
	uniform_real_distribution<float> distribution(i_value_min, nextafter(i_value_max, FLT_MAX));

	return distribution(random_engine);
}

int RandomManager::get_random(const int &i_value_max, const int &i_value_min)
{
	uniform_int_distribution<int> distribution(i_value_min, i_value_max);

	return distribution(random_engine);
}
