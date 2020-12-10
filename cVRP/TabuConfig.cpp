#include "TabuConfig.h"
#include "DefaultConfig.h"

TabuConfig::TabuConfig()
{
  m_neighbours = config::NEIGHBOURS;
  m_iterations = config::ITERATIONS;
  m_instance_problem = PROBLEM_A_N32_K5;
  m_tabu_size = config::TABU_SIZE;
  m_neighbourhood_type = MutationType::SWAP;
}

void TabuConfig::setNeighbours(int t_neighbours)
{
  m_neighbours = t_neighbours;
}

void TabuConfig::setIterations(int t_iterations)
{
  m_iterations = t_iterations;
}

void TabuConfig::setTabuSize(int t_tabu_size)
{
  m_tabu_size = t_tabu_size;
}

int TabuConfig::getNeighbours()
{
  return m_neighbours;
}

int TabuConfig::getIterations()
{
  return m_iterations;
}

int TabuConfig::getTabuSize()
{
  return m_tabu_size;
}

MutationType TabuConfig::getNeighbourhoodType()
{
    return m_neighbourhood_type;
}
