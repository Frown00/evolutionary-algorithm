#pragma once
#include "ProblemNames.h"
#include "Evolution.h"

namespace config {
	using namespace evolution;
	// path to file with vehicle routing problem
	const std::string INSTANCE_PROBLEM = PROBLEM_A_N60_K9;
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

	const MutationType MUTATION_TYPE = MutationType::INVERSION;
	const CrossoverType CROSSOVER_TYPE = CrossoverType::CYCLE;
	const SelectionType SELECTION_TYPE = SelectionType::TOURNAMENT;

	// TABU SEARCH
	const int NEIGHBOURS = 5;
	const int ITERATIONS = 100;
	const int TABU_SIZE = 20;
};
