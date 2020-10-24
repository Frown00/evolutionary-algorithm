
#include "Evolution.h"

Evolution::Evolution(VehicleRoutingProblem* t_problem) {
	m_problem = t_problem;
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
