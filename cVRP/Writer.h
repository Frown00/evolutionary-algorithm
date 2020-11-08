#pragma once
#include "utils.cpp"
#include "Config.h"
#include "Summary.h"
#include <fstream>
class Writer
{
	public:
		void saveResults(Summary* t_greedy, Summary* t_random, std::vector<Summary*> evolution);
};

