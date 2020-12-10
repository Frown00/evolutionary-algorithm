#include "SAConfig.h"
#include "DefaultConfig.h"

SAConfig::SAConfig()
{
	m_instance_problem = PROBLEM_A_N32_K5;
	m_neighbours = config::NEIGHBOURS_SA;
	m_iterations = config::ITERATIONS_SA;
	m_temp_start = config::TEMP_START;
	m_temp_stop = config::TEMP_STOP;
	m_cooling_rate = config::COOLING_RATE;
	m_neighbourhood_type = MutationType::SWAP;
}

void SAConfig::setNeighbours(int t_neighbours)
{
	m_neighbours = t_neighbours;
}

void SAConfig::setIterations(int t_iterations)
{
	m_iterations = t_iterations;
}

void SAConfig::setTemperature(double t_start, double t_stop, double t_cooling_rate)
{
	m_temp_start = t_start;
	m_temp_stop = t_stop;
	m_cooling_rate = t_cooling_rate;
}

int SAConfig::getNeighbours()
{
	return m_neighbours;
}

int SAConfig::getIterations()
{
	return m_iterations;
}

double SAConfig::getTempStart()
{
	return m_temp_start;
}

double SAConfig::getTempStop()
{
	return m_temp_stop;
}

double SAConfig::getCoolingRate()
{
	return m_cooling_rate;
}

MutationType SAConfig::getNeighbourhoodType()
{
	return m_neighbourhood_type;
}
