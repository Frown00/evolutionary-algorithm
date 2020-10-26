#pragma once
#include "ProblemPaths.h"
#include "Evolution.h"

namespace config {
	using namespace evolution;
	// path to file with vehicle routing problem
	const std::string FILENAME = PROBLEM_A_N32_K5;

	// population size
	const int POP_SIZE = 100;

	// generations amount
	const int GEN = 100;

	// percent chance for crossing
	const double P_X = 70;

	// percent chance for mutation
	const double P_M = 10;

	// used for tournament selection
	// percent of current population which participate in one tournament
	const double TOUR = 5;

	const MutationType MUTATION_TYPE = MutationType::SWAP;
	const CrossoverType CROSSOVER_TYPE = CrossoverType::ORDERED;
	const SelectionType SELECTION_TYPE = SelectionType::ROULETTE;
};
