#pragma once
#include "Loader.h"
#include "Evolution.h"
#include <time.h>
#include "Writer.h"
#include "Config.h"
#include "TabuSearch.h"

using namespace evolution;

int main()
{
  srand((unsigned int)time(NULL));
  Loader* loader = new Loader();
  Writer* writer = new Writer();
  loader->readFile();
  VehicleRoutingProblem* problem = loader->getProblem();
  Summary* greedy = problem->greedySolution();
  Summary* random = problem->randomSolution(1);
  Evolution* ea = new Evolution(problem);
  std::vector<Summary*> evolution = ea->solve(1);
  writer->openEvolutionFile();
  writer->saveGreedy(greedy);
  writer->saveRandom(random);
  writer->saveEvolution(evolution);
  writer->close();
  //TabuSearch* tabu = new TabuSearch(problem);
  //std::vector<Summary*> ts = tabu->solve(1);
}
