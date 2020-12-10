#pragma once
#include <vector>
#include "Individual.h"
#include "Experiment.h"
#include "Summary.h"
#include "VehicleRoutingProblem.h"
#include <algorithm>  
#include <iostream> 
#include "TabuConfig.h"
#include "Test.h"

class TabuSearch
{
	public:
		TabuSearch(VehicleRoutingProblem* t_problem, TabuConfig* t_config);
		Summary* test(int t_test_num);
		Test* solve();
	private:
		TabuConfig* m_config;
		VehicleRoutingProblem* m_problem;
		std::vector<Individual*> m_tabu;
		std::vector<Individual*> findNeighbours(Individual* t_best_current);
		Individual* createInitialSolution();
		Individual* getBestTabuNeighbour(std::vector<Individual*> t_neighbourhood);
		bool isTabu(Individual* t_individual);
		void updateTabu(
			std::vector<Individual*> t_neighbourhood
		);
};

