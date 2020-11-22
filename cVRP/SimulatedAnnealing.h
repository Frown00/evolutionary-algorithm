#pragma once
#include "VehicleRoutingProblem.h"
#include <vector>
#include "Individual.h"
#include "Summary.h"
#include "VehicleRoutingProblem.h"
#include "Config.h"
#include <algorithm>  
#include <iostream> 

class SimulatedAnnealing
{
	public:
		SimulatedAnnealing(VehicleRoutingProblem* t_problem);
		Summary* test(int t_test_num);
		Test* solve();

	private:
		VehicleRoutingProblem* m_problem;
		std::vector<Individual*> findNeighbours(Individual* t_best_current);
		Individual* createInitialSolution();
		Individual* getBestNeighbour(std::vector<Individual*> t_neighbourhood);
		double P(double dE, double T) {
			if (dE < 0) {
				return 1;
			}
			else {
				return std::exp((-dE) / T);
			}
		}
		double temperature(double T) {
			return T - 1;
		}
		
};

