#pragma once
#include "Loader.h"
#include "Evolution.h"
#include <time.h>

using namespace evolution;

int main()
{
  srand((unsigned int)time(NULL));
  Loader* loader = new Loader();
  loader->readFile();
  VehicleRoutingProblem* problem = loader->getProblem();
  std::cout << "GREEDY SOLUTION";
  Summary* greedy = problem->greedySolution();
  std::cout << "\n\nRANDOM SOLUTION";
  Summary* random = problem->randomSolution(10);
  std::cout << rand() % 100;
  Evolution evolution = Evolution(problem);
  evolution.solve();
  evolution.saveResults(greedy, random);
}
