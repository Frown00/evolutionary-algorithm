#pragma once
#include "utils.cpp"
#include "Summary.h"
#include <fstream>
#include "Test.h"
#include "EvolutionConfig.h"
#include "SAConfig.h"
#include "TabuConfig.h"

class Writer
{
	public:
		void openEvolutionFile(EvolutionConfig* t_config);
		void openTabuFile(TabuConfig* t_config);
		void openAnealingFile(SAConfig* t_config);
		void openOverallFile(std::string name);
		void saveOverall(std::vector<std::string> problems, std::vector<Summary*> t_overall);
		void saveGreedy(Summary* t_greedy);
		void saveRandom(Summary* t_random);
		void saveEvolution(Test* t_evolution);
		void saveTabu(Test* t_tabu);
		void saveAnealing(Test* t_anealing);
		void close();
	
	private:
		std::ofstream m_file;
};

