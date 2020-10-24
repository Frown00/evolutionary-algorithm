#pragma once
#include "Loader.h"
#include "Evolution.h"
#include <time.h>

int main()
{
  srand((unsigned int)time(NULL));
  Loader* loader = new Loader();
  loader->readFile();
  VehicleRoutingProblem* problem = loader->getProblem();
  Evolution evolution = Evolution(problem);
  evolution.createPopulation();
}
