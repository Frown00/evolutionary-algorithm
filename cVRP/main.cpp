#pragma once
#include "Loader.h"
#include "Evolution.h"
#include <time.h>
#include "Writer.h"
#include "Config.h"

using namespace evolution;

int main()
{
  srand((unsigned int)time(NULL));
  Loader* loader = new Loader();
  loader->readFile();
  VehicleRoutingProblem* problem = loader->getProblem();
  Summary* greedy = problem->greedySolution();
  Summary* random = problem->randomSolution(10000);
  Evolution* ea = new Evolution(problem);
  std::vector<Summary*> evolution = ea->solve(10);
  Writer* writer = new Writer();
  writer->saveResults(greedy, random, evolution);
}
