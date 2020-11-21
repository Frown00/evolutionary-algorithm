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
		void openAnealingFile();
		void saveGreedy(Summary* t_greedy);
		void saveRandom(Summary* t_random);
		void saveEvolution(Test* t_evolution);
		void saveTabu(std::vector<Summary*> t_tabu);
		void saveAnealing(std::vector<Summary*> t_anealing);
		void close();
	
	private:
		std::ofstream m_file;
};

