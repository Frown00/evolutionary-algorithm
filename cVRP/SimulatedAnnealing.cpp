#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(VehicleRoutingProblem* t_problem)
{
	m_problem = t_problem;
}

std::vector<Summary*> SimulatedAnnealing::solve(int t_test_num)
{
	Experiment* experiment = new Experiment();
	for (int t = 1; t <= t_test_num; t++) {
		Test* test = new Test(t);
		std::cout << "\n\nSIMULATED ANNEALING TEST: " << t << "\n";
		Individual* best_current = createInitialSolution();
		double temp_start = 100;
		double cooling_rate = 1;
		double temp_end = 0;
		double T = temp_start;
		int i = 1;
		while (i <= config::ITERATIONS) {
			Summary* summary = new Summary(i);
			std::cout << "\r" << "PROGRESS: " << i << " / " << config::ITERATIONS;
			std::vector<Individual*> neighbours = findNeighbours(best_current);
			Individual* best_neighbour = getBestNeighbour(neighbours);
			double dE = best_neighbour->getFitness() - best_current->getFitness();
			double r = (double)rand() / RAND_MAX;
			double p = P(dE, T);
			if(r < p) {
				best_current = new Individual(best_neighbour);
			}
			T = std::max(T-cooling_rate, temp_end);
			summary->addResult(best_current);
			/*for (int n = 0; n < neighbours.size(); n++) {
				summary->addResult(neighbours[n]);
			}*/
			test->addSummary(summary);
			summary->countAverage();
			i++;
		}
		std::cout << "\n\n" << "BEST PATH:";
		test->getBestRoute()->printRouting(m_problem->getDepot());
		experiment->addTest(test);
	}
	std::cout << "\nCOMPLETED\n";
	return experiment->getOverallSummary();
}

std::vector<Individual*> SimulatedAnnealing::findNeighbours(Individual* t_best_current)
{
	std::vector<Individual*> neigbourhood;
	for (int i = 0; i < config::NEIGHBOURS; i++) {
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

Individual* SimulatedAnnealing::createInitialSolution()
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

Individual* SimulatedAnnealing::getBestNeighbour(std::vector<Individual*> t_neighbourhood)
{
	Individual* best = nullptr;
	for (int i = 0; i < t_neighbourhood.size(); i++) {
		if (best == nullptr) {
			best = t_neighbourhood[i];
		}
		else if (t_neighbourhood[i]->getFitness() < best->getFitness()) {
			best = t_neighbourhood[i];
		}
	}
	return best;
}
