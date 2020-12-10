#include "TabuSearch.h"

TabuSearch::TabuSearch(VehicleRoutingProblem* t_problem, TabuConfig* t_config)
{
	m_problem = t_problem;
	m_tabu = std::vector<Individual*>();
	m_config = t_config;
}

Test* TabuSearch::solve()
{
	Test* test = new Test(0);
	std::cout << "\n\nTABU SEARCH TEST: " << "\n";
	m_tabu.clear();
	Individual* best_current = createInitialSolution();
	m_tabu.push_back(best_current);
	int i = 1;
	while(i <= m_config->getIterations()) {
		Summary* summary = new Summary(i);
		std::cout << "\r" << "PROGRESS: " << i << " / " << m_config->getIterations();
		std::vector<Individual*> neighbours = findNeighbours(best_current);
		int k = neighbours.size();
		for(int n = 0; n < k; n++) {
			summary->addResult(neighbours[n]);
		}
		Individual* best_neighbour = getBestTabuNeighbour(neighbours);
		if(best_neighbour != nullptr) {
			// do nothing 
			best_current = new Individual(best_neighbour);
		}
		updateTabu(neighbours);
		summary->countAverage();
		test->addSummary(summary);
		i++;
	}
	std::cout << "\n\n" << "BEST PATH:";
	test->getBestRoute()->printRouting(m_problem->getDepot());
	return test;
}

Summary* TabuSearch::test(int t_test_num)
{
	Experiment* experiment = new Experiment();
	for(int t = 1; t <= t_test_num; t++) {
		Test* test = new Test(t);
		std::cout << "\n\nTABU SEARCH TEST: " << t << "\n";
		m_tabu.clear();
		Individual* best_current = createInitialSolution();
		m_tabu.push_back(best_current);
		int i = 1;
		while(i <= m_config->getIterations()) {
			Summary* summary = new Summary(i);
			std::cout << "\r" << "PROGRESS: " << i << " / " << m_config->getIterations();
			std::vector<Individual*> neighbours = findNeighbours(best_current);
			int k = neighbours.size();
			for(int n = 0; n < k; n++) {
				summary->addResult(neighbours[n]);
			}
			Individual* best_neighbour = getBestTabuNeighbour(neighbours);
			if(best_neighbour != nullptr) { 
				// do nothing 
				best_current = new Individual(best_neighbour);
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

std::vector<Individual*> TabuSearch::findNeighbours(Individual* t_best_current)
{
	std::vector<Individual*> neigbourhood;
	for(int i = 0; i < m_config->getNeighbours(); i++) {
		Individual* neighbour = new Individual(m_problem->getDimension());
		neighbour->setGenotype(t_best_current->getGenotype());
		neighbour->mutate(
			m_config->getNeighbourhoodType(),
			m_problem->getDepot(),
			m_problem->getLocations(),
			m_problem->getCapacity()
		);
		neighbour->countFitness(m_problem->getDepot(), m_problem->getLocations());
		neigbourhood.push_back(neighbour);
	}
	return neigbourhood;
}

Individual* TabuSearch::getBestTabuNeighbour(std::vector<Individual*> t_neighbourhood)
{
	Individual* best = nullptr;
	for(int i = 0; i < t_neighbourhood.size(); i++) {
		Individual* neighbour = t_neighbourhood[i];
		if(best == nullptr) {
			if(!isTabu(neighbour)) {
				best = neighbour;
			}
		}
		else if(neighbour->getFitness() < best->getFitness()) {
			if(!isTabu(neighbour)) {
				best = neighbour;
			}
		}
	}
	return best;
}

bool TabuSearch::isTabu(Individual* t_individual)
{
	std::string genotype = t_individual->getTextGenotype();
	int tabu_size = m_tabu.size();
	for(int i = 0; i < tabu_size; i++) {
		std::string other_genotype = m_tabu[i]->getTextGenotype();
		if(other_genotype == genotype) {
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
	int tabu_excess = int(m_tabu.size() - m_config->getTabuSize());
	int excess = std::max(tabu_excess, 0);
	for(int i = 0; i < excess; i++) {
		m_tabu.erase(m_tabu.begin());
	}
}


