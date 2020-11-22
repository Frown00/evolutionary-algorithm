#pragma once
#include "ProblemNames.h"
#include "Evolution.h"

namespace config {
	using namespace evolution;
	// path to file with vehicle routing problem
	const std::string INSTANCE_PROBLEM = PROBLEM_A_N32_K5;
	const std::string FILENAME = "./problems/" + INSTANCE_PROBLEM + ".vrp";

	// population size
	const int POP_SIZE = 1000;

	// generations amount
	const int GEN = 100;

	// percent chance for crossing
	const double P_X = 70;

	// percent chance for mutation
	const double P_M = 20;

	// used for tournament selection
	// percent of current population which participate in one tournament
	const double TOUR = 10;

	const MutationType MUTATION_TYPE = MutationType::SWAP;
	const CrossoverType CROSSOVER_TYPE = CrossoverType::CYCLE;
	const SelectionType SELECTION_TYPE = SelectionType::TOURNAMENT;

	// TABU SEARCH
	const int NEIGHBOURS = 1;
	const int ITERATIONS = 10000;
	const int TABU_SIZE = 20;

	// SIMULATED ANNEALING
	const int NEIGHBOURS_SA = 1;
	const int ITERATIONS_SA = 100000;
	const double TEMP_START = 10000;
	const double TEMP_STOP = 0.01;
	const double COOLING_RATE = 0.99986;
};
