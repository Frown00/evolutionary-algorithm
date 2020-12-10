#pragma once
#include <vector>
#include "Individual.h"
#include "Location.h"
#include "VehicleRoutingProblem.h"
#include "Experiment.h"
#include "EvolutionConfig.h"


class Evolution {
	
	public:
		Evolution(VehicleRoutingProblem* t_problem, EvolutionConfig* t_config);
		Summary* test(int t_test_num);
		Test* solve();
	
	private:
		EvolutionConfig* m_config;
		std::vector<Individual*> createPopulation();
		void mutation(std::vector<Individual*> t_population);
		void crossover(std::vector<Individual*> t_population, std::vector<Individual*> &t_new_population);
		std::vector<Individual*> tournamentSelection(std::vector<Individual*> t_population);
		std::vector<Individual*> rouletteSelection(std::vector<Individual*> t_population);
		std::vector<Individual*> selection(std::vector<Individual*> t_population);
		void refreshFitness(std::vector<Individual*> t_population);
		VehicleRoutingProblem* m_problem;

};

