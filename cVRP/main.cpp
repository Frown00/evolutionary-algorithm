#pragma once
#include "Loader.h"
#include "Evolution.h"
#include <time.h>
#include "Writer.h"
#include "Config.h"
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"

using namespace evolution;

int main()
{
  srand((unsigned int)time(NULL));
  Loader* loader = new Loader();
  Writer* writer = new Writer();
  loader->readFile();
  VehicleRoutingProblem* problem = loader->getProblem();
  /*Summary* greedy = problem->greedySolution();
  Summary* random = problem->randomSolution(10000);*/
 /* Evolution* ea = new Evolution(problem);
  Test* evolution = ea->solve();
  writer->openEvolutionFile();
  writer->saveGreedy(greedy);
  writer->saveRandom(random);
  writer->saveEvolution(evolution);
  writer->close();*/
 /* Summary* overall = ea->test(10);
  std::cout << "\n\nBEST: " << overall->getBest();
  std::cout << "\nWORST: " << overall->getWorst();
  std::cout << "\nAVG: " << overall->getAverage();
  std::cout << "\nSTD: " << overall->getStd();*/
  
  /*TabuSearch* tabu = new TabuSearch(problem);
  Test* tabu_search = tabu->solve();
  writer->openAnealingFile();
  writer->saveGreedy(greedy);
  writer->saveRandom(random);
  writer->saveAnealing(tabu_search);
  writer->close();*/
  //std::cout << "\n\nBEST: " << tabu_search->getBest();
  //std::cout << "\nWORST: " << tabu_search->getWorst();
  //std::cout << "\nAVG: " << tabu_search->getAverage();
  //std::cout << "\nSTD: " << tabu_search->getStd();
  int a = 3;
 /* writer->openTabuFile();
  writer->saveGreedy(greedy);
  writer->saveRandom(random);
  writer->saveTabu(tabu_search);
  writer->close();*/
  SimulatedAnnealing* sa = new SimulatedAnnealing(problem);
  //Test* anealing = sa->solve();
  //writer->openAnealingFile();
  ////writer->saveGreedy(greedy);
  ////writer->saveRandom(random);
  //writer->saveAnealing(anealing);
  //writer->close();

  Summary* overall = sa->test(10);
  std::cout << "\n\nBEST: " << overall->getBest();
  std::cout << "\nWORST: " << overall->getWorst();
  std::cout << "\nAVG: " << overall->getAverage();
  std::cout << "\nSTD: " << overall->getStd();
}
