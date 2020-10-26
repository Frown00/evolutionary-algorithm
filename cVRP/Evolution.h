#pragma once
#include <vector>
#include "Individual.h"
#include "Location.h"
#include "VehicleRoutingProblem.h"

namespace evolution {
	const enum class MutationType {
		SWAP = 0,
		INVERSION = 1,
	};

	const enum class CrossoverType {
		ORDERED = 0,
		PARTIALLY_MATCHED = 1,
		CYCLE = 2
	};

	const enum class SelectionType {
		TOURNAMENT = 0,
		ROULETTE = 1
	};

	class Evolution {
	public:
		Evolution(VehicleRoutingProblem* t_problem);
		void solve();
	private:
		void createPopulation();
		void mutation();
		void crossover();
		void tournamentSelection();
		void rouletteSelection();
		void selection();
		void refreshFitness();
		VehicleRoutingProblem* m_problem;
		std::vector<Individual*> m_population;

	};
}

