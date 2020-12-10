#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(VehicleRoutingProblem* t_problem, SAConfig* t_config)
{
	m_problem = t_problem;
	m_config = t_config;
}

Test* SimulatedAnnealing::solve()
{
	Test* test = new Test(0);
	std::cout << "\n\nSIMULATED ANNEALING TEST: " << "\n";
	Individual* best_current = createInitialSolution();
	double temp_start = m_config->getTempStart();
	double temp_end = m_config->getTempStop();
	double cooling_rate = m_config->getCoolingRate();
	int iterations = m_config->getIterations();
	double T = temp_start;
	int i = 1;
	int neighbours_number = m_config->getNeighbours();
	MutationType neighbourhood_type = m_config->getNeighbourhoodType();
	Location* depot = m_problem->getDepot();
	std::vector<Location*> locations = m_problem->getLocations();
	int max_capacity = m_problem->getCapacity();
	int dimension = m_problem->getDimension();

	while(T > temp_end) {
		if (i == iterations) {
			break;
		}
		Summary* summary = new Summary();
		std::cout << "\r" << "PROGRESS: " << T << " / " << temp_end;
		std::vector<Individual*> neighbours = findNeighbours(
			best_current,
			neighbours_number,
			neighbourhood_type,
			depot,
			locations,
			max_capacity,
			dimension
		);
		Individual* best_neighbour = getBestNeighbour(neighbours);
		double dE = best_neighbour->getFitness() - best_current->getFitness();
		double r = (double)rand() / RAND_MAX;
		double p = P(dE, T);
		if (r < p) {
			best_current = new Individual(best_neighbour);
		}
		T *= cooling_rate;
		summary->addResult(best_current);
		test->addSummary(summary);
		summary->countAverage();
		i++;
		
	}
	std::cout << "\n\n" << "BEST PATH:";
	test->getBestRoute()->printRouting(m_problem->getDepot());
	return test;
}

Summary* SimulatedAnnealing::test(int t_test_num)
{
	Experiment* experiment = new Experiment();
	for (int t = 1; t <= t_test_num; t++) {
		Test* test = new Test(t);
		std::cout << "\n\nSIMULATED ANNEALING TEST: " << t << "\n";
		Individual* best_current = createInitialSolution();
		double temp_start = m_config->getTempStart();
		double temp_end = m_config->getTempStop();
		double cooling_rate = m_config->getCoolingRate();
		int iterations = m_config->getIterations();
		double T = temp_start;
		int i = 1;
		int neighbours_number = m_config->getNeighbours();
		MutationType neighbourhood_type = m_config->getNeighbourhoodType();
		Location* depot = m_problem->getDepot();
		std::vector<Location*> locations = m_problem->getLocations();
		int max_capacity = m_problem->getCapacity();
		int dimension = m_problem->getDimension();

		while(T > temp_end) {
			if(i == iterations) {
				break;
			}
			Summary* summary = new Summary(i);
			std::cout << "\r" << "PROGRESS: " << T << " / " << temp_end;
			std::vector<Individual*> neighbours = findNeighbours(
				best_current,
				neighbours_number,
				neighbourhood_type,
				depot,
				locations,
				max_capacity,
				dimension
			);
			Individual* best_neighbour = getBestNeighbour(neighbours);
			double dE = best_neighbour->getFitness() - best_current->getFitness();
			double r = (double)rand() / RAND_MAX;
			double p = P(dE, T);
			if(r < p) {
				best_current = new Individual(best_neighbour);
			}
			T *= cooling_rate;
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

std::vector<Individual*> SimulatedAnnealing::findNeighbours(
	Individual* t_best_current,
	int t_neighbours,
	MutationType t_neighbourhood_type,
	Location* t_depot,
	std::vector<Location*> t_locations,
	int t_max_capacity,
	int t_dimension
)
{
	std::vector<Individual*> neigbourhood;
	for(int i = 0; i < t_neighbours; i++) {
		Individual* neighbour = new Individual(t_dimension);
		neighbour->setGenotype(t_best_current->getGenotype());
		neighbour->mutate(
			t_neighbourhood_type,
			t_depot,
			t_locations,
			t_max_capacity
		);
		neighbour->countFitness(t_depot, t_locations);
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
