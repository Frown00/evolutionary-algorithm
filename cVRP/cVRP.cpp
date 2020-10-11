#pragma once
#include "Loader.h"
#include "config.cpp"

int main()
{
  Loader* loader = new Loader();
  loader->readFile(config::FILENAME);
  VehicleRoutingProblem* problem = loader->getProblem();
}
