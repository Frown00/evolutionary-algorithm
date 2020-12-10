#include "EvolutionConfig.h"
#include "DefaultConfig.h"

EvolutionConfig::EvolutionConfig()
{
	m_instance_problem = PROBLEM_A_N32_K5;
	m_population_size = config::POP_SIZE;
	m_generations = config::GEN;
	m_px = config::P_X;
	m_pm = config::P_M;
	m_mutation_type = config::MUTATION_TYPE;
	m_crossover_type = config::CROSSOVER_TYPE;
	m_selection_type = config::SELECTION_TYPE;
	m_tour = config::TOUR;
}

void EvolutionConfig::setPopulationSize(int t_pop_size)
{
	m_population_size = t_pop_size;
}

void EvolutionConfig::setGenerations(int t_gen)
{
	m_generations = t_gen;
}

void EvolutionConfig::setPX(double t_px)
{
	m_px = t_px;
}

void EvolutionConfig::setPM(int t_pm)
{
	m_pm = t_pm;
}

void EvolutionConfig::setTournamentPercent(int t_tour)
{
	m_tour = t_tour;
}

void EvolutionConfig::setMutationType(MutationType m_type)
{
	m_mutation_type = m_type;
}

void EvolutionConfig::setCrossoverType(CrossoverType m_type)
{
	m_crossover_type = m_type;
}

void EvolutionConfig::setSelectionType(SelectionType m_type)
{
	m_selection_type = m_type;
}

double EvolutionConfig::getPX()
{
	return m_px;
}

double EvolutionConfig::getPM()
{
	return m_pm;
}

double EvolutionConfig::getTour()
{
	return m_tour;
}

int EvolutionConfig::getPopSize()
{
	return m_population_size;
}

int EvolutionConfig::getGenerations()
{
	return m_generations;
}

MutationType EvolutionConfig::getMutationType()
{
	return m_mutation_type;
}

CrossoverType EvolutionConfig::getCrossoverType()
{
	return m_crossover_type;
}

SelectionType EvolutionConfig::getSelectionType()
{
	return m_selection_type;
}

