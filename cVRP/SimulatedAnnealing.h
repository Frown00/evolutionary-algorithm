#pragma once
#include "VehicleRoutingProblem.h"
#include <vector>
#include "Individual.h"
#include "Summary.h"
#include "VehicleRoutingProblem.h"
#include <algorithm>  
#include <iostream> 
#include "SAConfig.h"
#include "Test.h"
#include "Experiment.h"

class SimulatedAnnealing
{
	public:
		SimulatedAnnealing(VehicleRoutingProblem* t_problem, SAConfig* t_config);
		Summary* test(int t_test_num);
		Test* solve();

	private:
		SAConfig* m_config;
		VehicleRoutingProblem* m_problem;
		std::vector<Individual*> findNeighbours(
			Individual* t_best_current,
			int t_neighbours,
			MutationType t_neighbourhood_type,
			Location* t_depot,
			std::vector<Location*> t_locations,
			int t_max_capacity,
			int t_dimension
		);
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

