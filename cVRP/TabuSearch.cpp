#include "TabuSearch.h"

TabuSearch::TabuSearch(VehicleRoutingProblem* t_problem)
{
	m_problem = t_problem;
	m_best_ever = new Individual(t_problem->getDimension());
	m_tabu = std::vector<Individual*>();
}

std::vector<Summary*> TabuSearch::solve(int t_test_num)
{
	Experiment* experiment = new Experiment();
	for(int t = 1; t <= t_test_num; t++) {
		Test* test = new Test(t);
		std::cout << "\n\nTABU SEARCH TEST: " << t << "\n";
		m_tabu.clear();
		Individual* best_current = createInitialSolution();
		m_tabu.push_back(best_current);
		int i = 1;
		while(i <= config::ITERATIONS) {
			Summary* summary = new Summary(i);
			std::cout << "\r" << "PROGRESS: " << i << " / " << config::ITERATIONS;
			std::vector<Individual*> neighbours = findNeighbours(best_current);
			for(int n = 0; n < neighbours.size(); n++) {
				summary->addResult(neighbours[n]);
			}
			Individual* best_neighbour = getBestTabuNeighbour(neighbours);
			if(best_neighbour == nullptr) { 
				// do nothing 
			}
			else if(best_neighbour->getFitness() < best_current->getFitness()) {
				best_current = best_neighbour;
			}
			updateTabu(neighbours);
			summary->countAverage();
			test->addSummary(summary);
			i++;
		}
		std::cout << "\n\n" << "BEST PATH:";
		test->getBestRoute()->printRouting(m_problem->getDepot());
		experiment->addTest(test);
	}
	std::cout << "\nCOMPLETED\n";
	return experiment->getOverallSummary();
}

std::vector<Individual*> TabuSearch::findNeighbours(Individual* t_best_current)
{
	std::vector<Individual*> neigbourhood;
	for(int i = 0; i < config::NEIGHBOURS; i++) {
		Individual* neighbour = new Individual(m_problem->getDimension());
		neighbour->setGenotype(t_best_current->getGenotype());
		neighbour->mutate(
			m_problem->getDepot(),
			m_problem->getLocations(),
			m_problem->getCapacity()
		);
		neighbour->countFitness(m_problem->getDepot(), m_problem->getLocations());
		neigbourhood.push_back(neighbour);
	}
	return neigbourhood;
}

Individual* TabuSearch::createInitialSolution()
{
	Individual* initial = new Individual(m_problem->getDimension());
	initial->setRandomGenotype(
		m_problem->getDepot(),
		m_problem->getLocations(),
		m_problem->getCapacity()
	);
	initial->countFitness(m_problem->getDepot(), m_problem->getLocations());
	return initial;
}

Individual* TabuSearch::getBestTabuNeighbour(std::vector<Individual*> t_neighbourhood)
{
	Individual* best = nullptr;
	for(int i = 0; i < t_neighbourhood.size(); i++) {
		if(best == nullptr) {
			if(isTabu(t_neighbourhood[i])) {
				best = t_neighbourhood[i];
			}
		}
		else if(t_neighbourhood[i]->getFitness() < best->getFitness()) {
			if(isTabu(t_neighbourhood[i])) {
				best = t_neighbourhood[i];
			}
		}
	}
	return best;
}

bool TabuSearch::isTabu(Individual* t_individual)
{
	for(int i = 0; i < m_tabu.size(); i++) {
		if(m_tabu[i]->getTextGenotype() == t_individual->getTextGenotype()) {
			return true;
		}
	}
	return false;
}

void TabuSearch::updateTabu(std::vector<Individual*> t_neighbourhood)
{
	for(int i = 0; i < t_neighbourhood.size(); i++) {
		m_tabu.push_back(t_neighbourhood[i]);
	}
	int excess = std::max(int(m_tabu.size() - config::TABU_SIZE), 0);
	for(int i = 0; i < excess; i++) {
		m_tabu.erase(m_tabu.begin() + i);
	}
}


