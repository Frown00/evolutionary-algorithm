#include "ProblemPaths.h"

namespace config {
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
	// number of individuals participating in one tournament
	const double TOUR = 5;													
};
