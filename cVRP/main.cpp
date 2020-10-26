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
  Summary* greedy = problem->greedySolution();
  Summary* random = problem->randomSolution(10000);
  Evolution evolution = Evolution(problem);
  evolution.solve(10);
  evolution.saveResults(greedy, random);
}
