#pragma once
#include "utils.cpp"
#include "Config.h"
#include "Summary.h"
#include <fstream>
class Writer
{
	public:
		void openEvolutionFile();
		void openTabuFile();
		void saveGreedy(Summary* t_greedy);
		void saveRandom(Summary* t_random);
		void saveEvolution(std::vector<Summary*> t_evolution);
		void saveTabu(std::vector<Summary*> t_tabu);
		void close();
	
	private:
		std::ofstream m_file;
};

