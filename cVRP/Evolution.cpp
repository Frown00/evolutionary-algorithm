
#include "Evolution.h"
#include "Config.h"

using namespace evolution;

Evolution::Evolution(VehicleRoutingProblem* t_problem) {
	m_problem = t_problem;
}

void Evolution::solve() {
	createPopulation();
	mutation();
	//crossover();
	//selection();
}

void Evolution::createPopulation() {
	for(int i = 0; i < config::POP_SIZE; i++) {
		Individual* individual = new Individual(m_problem->getDimension());
		individual->setRandomGenotype(
			m_problem->getDepot(),
			m_problem->getLocations(),
			m_problem->getCapacity()
		);
		individual->countFitness(m_problem->getDepot(), m_problem->getLocations());
		m_population.push_back(individual);
	}
}

void Evolution::mutation() {
	for(int i = 0; i < m_population.size(); i++) {
		Individual* individual = m_population[i];
		int chance = rand() % 100;
		if(chance < config::P_M) {
			individual->mutate(
				m_problem->getDepot(), 
				m_problem->getLocations(), 
				m_problem->getCapacity()
			);
		}
	}
}

void Evolution::crossover() {
}
