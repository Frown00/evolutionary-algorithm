#pragma once
#include <vector>
#include "Individual.h"
#include "Location.h"
#include "VehicleRoutingProblem.h"
#include "Experiment.h"

namespace evolution {
	const enum class MutationType {
		SWAP = 0,
		INVERSION = 1,
	};

	const enum class CrossoverType {
		ORDERED = 0,
		CYCLE = 1
	};

	const enum class SelectionType {
		TOURNAMENT = 0,
		ROULETTE = 1
	};

	class Evolution {
	
		public:
			Evolution(VehicleRoutingProblem* t_problem);
			Summary* test(int t_test_num);
			Test* solve();
	
		private:
			std::vector<Individual*> createPopulation();
			void mutation(std::vector<Individual*> t_population);
			void crossover(std::vector<Individual*> t_population, std::vector<Individual*> &t_new_population);
			std::vector<Individual*> tournamentSelection(std::vector<Individual*> t_population);
			std::vector<Individual*> rouletteSelection(std::vector<Individual*> t_population);
			std::vector<Individual*> selection(std::vector<Individual*> t_population);
			void refreshFitness(std::vector<Individual*> t_population);
			VehicleRoutingProblem* m_problem;

	};
}

