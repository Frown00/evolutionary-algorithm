#pragma once
#include <vector>
#include "Individual.h"
#include "Summary.h"
#include "VehicleRoutingProblem.h"
#include "Config.h"
#include <algorithm>  
#include <iostream> 

class TabuSearch
{
	public:
		TabuSearch(VehicleRoutingProblem* t_problem);
		Summary* test(int t_test_num);
		Test* solve();
	private:
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

