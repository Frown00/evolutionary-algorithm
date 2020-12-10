#pragma once
#include "Loader.h"
#include "Evolution.h"
#include <time.h>
#include "Writer.h"
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"
#include "SAConfig.h"
#include "ProblemNames.h"

int main()
{
  srand((unsigned int)time(NULL));
  const std::vector<std::string> problems = {
    PROBLEM_A_N32_K5,
    PROBLEM_A_N37_K6,
    PROBLEM_A_N39_K5,
    PROBLEM_A_N45_K6,
    PROBLEM_A_N48_K7,
    PROBLEM_A_N54_K7,
    PROBLEM_A_N60_K9
  };
  std::vector<Summary*> problems_stats;
 
  Loader* loader = new Loader();
  Writer* writer = new Writer();
  /*writer->openOverallFile(
    "greedy-"
  );
  for(int i = 0; i < problems.size(); i++) {
    EvolutionConfig* config = new EvolutionConfig();
    std::string current_problem = problems[i];
    config->setProblem(current_problem);
    loader->readFile(config);
    VehicleRoutingProblem* problem = loader->getProblem();
    Summary* greedy = problem->greedySolution();
    problems_stats.push_back(greedy);
  }
  writer->saveOverall(problems, problems_stats);
  writer->close();

  writer->openOverallFile(
    "random-"
  );
  problems_stats.clear();
  for (int i = 0; i < problems.size(); i++) {
    EvolutionConfig* config = new EvolutionConfig();
    std::string current_problem = problems[i];
    config->setProblem(current_problem);
    loader->readFile(config);
    VehicleRoutingProblem* problem = loader->getProblem();
    Summary* random = problem->randomSolution(10000);
    problems_stats.push_back(random);
  }
  writer->saveOverall(problems, problems_stats);
  writer->close();
  problems_stats.clear();*/

  //EvolutionConfig* config = new EvolutionConfig();
  //std::string current_problem = PROBLEM_A_N60_K9;
  //config->setProblem(current_problem);
  //loader->readFile(config);
  //writer->openEvolutionFile(config);
  //VehicleRoutingProblem* problem = loader->getProblem();
  //Evolution* ea = new Evolution(problem, config);
  //Test* evolution = ea->solve();
  //writer->saveEvolution(evolution);

  TabuConfig* config = new TabuConfig();
  std::string current_problem = PROBLEM_A_N60_K9;
  config->setProblem(current_problem);
  loader->readFile(config);
  writer->openTabuFile(config);
  VehicleRoutingProblem* problem = loader->getProblem();
  TabuSearch* ts = new TabuSearch(problem, config);
  Test* tabu = ts->solve();
  writer->saveTabu(tabu);

  /*SAConfig* config = new SAConfig();
  std::string current_problem = PROBLEM_A_N60_K9;
  config->setProblem(current_problem);
  loader->readFile(config);
  writer->openAnealingFile(config);
  VehicleRoutingProblem* problem = loader->getProblem();
  SimulatedAnnealing* sa = new SimulatedAnnealing(problem, config);
  Test* simulated = sa->solve();
  writer->saveAnealing(simulated);*/
 

  // EVOLUTION
  //writer->openOverallFile(
  //  "ea-" +
  //  std::to_string(config::POP_SIZE) + '-' +
  //  std::to_string(config::GEN) + '-' +
  //  std::to_string(config::P_M) + '-' +
  //  std::to_string(config::P_X)
  //);
  //for(int i = 0; i < problems.size(); i++) {
  //  EvolutionConfig* config = new EvolutionConfig();
  //  std::string current_problem = problems[i];
  //  config->setProblem(current_problem);
  //  loader->readFile(config);
  //  VehicleRoutingProblem* problem = loader->getProblem();
  //  Evolution* ea = new Evolution(problem, config);
  //  Summary* overall = ea->test(10);
  //  delete ea;
  //  problems_stats.push_back(overall);
  //}
  //writer->saveOverall(problems, problems_stats);
  //writer->close();

  // TABU SEARCH
  /*problems_stats.clear();
  writer->openOverallFile(
    "ts-" +
    std::to_string(config::ITERATIONS) + '-' +
    std::to_string(config::NEIGHBOURS) + '-' +
    std::to_string(config::TABU_SIZE) + '-' +
    std::to_string(config::COOLING_RATE)
  );
  for(int i = 0; i < problems.size(); i++) {
    TabuConfig* config = new TabuConfig();
    std::string current_problem = problems[i];
    config->setProblem(current_problem);
    loader->readFile(config);
    VehicleRoutingProblem* problem = loader->getProblem();
    TabuSearch* tabu = new TabuSearch(problem, config);
    Summary* overall = tabu->test(10);
    problems_stats.push_back(overall);
  }

  writer->saveOverall(problems, problems_stats);
  writer->close();*/

  // SIMULATED ANNEALING
  /*problems_stats.clear();
  writer->openOverallFile(
    "sa-" +
    std::to_string(config::ITERATIONS_SA) + '-' +
    std::to_string(config::NEIGHBOURS_SA) + '-' +
    std::to_string(config::TEMP_START) + '-' +
    std::to_string(config::TEMP_STOP) + '-' +
    std::to_string(config::COOLING_RATE)
  );
  for(int i = 0; i < problems.size(); i++) {
    SAConfig* config = new SAConfig();
    config->setProblem(problems[i]);
    loader->readFile(config);
    VehicleRoutingProblem* problem = loader->getProblem();
    SimulatedAnnealing* sa = new SimulatedAnnealing(problem, config);
    Summary* overall = sa->test(10);
    problems_stats.push_back(overall);
  }
  writer->saveOverall(problems, problems_stats);
  writer->close();*/
}
