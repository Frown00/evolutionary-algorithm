#pragma once
#include "ProblemNames.h"
#include "Enums.h"
namespace config {
	// path to file with vehicle routing problem

	// population size
	const int POP_SIZE = 1000;
	// generations amount
	const int GEN = 1000;
	// percent chance for crossing
	const double P_X = 80;
	// percent chance for mutation
	const double P_M = 20;
	// used for tournament selection
	// percent of current population which participate in one tournament
	const double TOUR = 5;
	const MutationType MUTATION_TYPE = MutationType::INVERSION;
	const CrossoverType CROSSOVER_TYPE = CrossoverType::CYCLE;
	const SelectionType SELECTION_TYPE = SelectionType::TOURNAMENT;

	// TABU SEARCH
	const int NEIGHBOURS = 50;
	const int ITERATIONS = 2000;
	const int TABU_SIZE = 500;

	// SIMULATED ANNEALING
	const int NEIGHBOURS_SA = 1;
	const int ITERATIONS_SA = 100000;
	const double TEMP_START = 10000;
	const double TEMP_STOP = 0.01;
	const double COOLING_RATE = 0.99986;
};
