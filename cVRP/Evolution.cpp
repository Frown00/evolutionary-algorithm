
#include "Evolution.h"
#include "DefaultConfig.h"
#include <fstream>
#include <string> 

Evolution::Evolution(VehicleRoutingProblem* t_problem, EvolutionConfig* t_config) {
	m_problem = t_problem;
	m_config = t_config;
}

Test* Evolution::solve()
{
	Test* test = new Test(0);
	std::cout << "\nEVOLUTION" << "\n";
	std::vector<Individual*> new_population = createPopulation();
	const int pop_size = m_config->getPopSize();
	for (int g = 1; g <= m_config->getGenerations(); g++) {
		Summary* generation_summary = new Summary(g);
		std::cout << "\r" << "EVOLUTION PROGRESS: " << g << " / " << m_config->getGenerations();
		std::vector<Individual*> current_population = selection(new_population);
		for (int i = 0; i < pop_size; i++) {
			generation_summary->addResult(new_population[i]);
		}
		generation_summary->countAverage();
		generation_summary->countStd();
		test->addSummary(generation_summary);
		new_population.clear();
		crossover(current_population, new_population);
		mutation(new_population);
		refreshFitness(new_population);
	}
	std::cout << "\n\n" << "BEST PATH:";
	test->getBestRoute()->printRouting(m_problem->getDepot());
	return test;
}



Summary* Evolution::test(int t_test_num) {
	Experiment* experiment = new Experiment();
	for(int t = 1; t <= t_test_num; t++) {
		Test* test = new Test(t);
		std::cout << "\nEVOLUTION TEST: " << t << "\n";
		std::vector<Individual*> new_population = createPopulation();
		for(int g = 1; g <= m_config->getGenerations(); g++) {
			Summary* generation_summary = new Summary(g);
			std::cout << "\r" << "EVOLUTION PROGRESS: " << g << " / " << m_config->getGenerations();
			for(int i = 0; i < new_population.size(); i++) {
				generation_summary->addResult(new_population[i]);
			}
			generation_summary->countAverage();
			test->addSummary(generation_summary);
			std::vector<Individual*> current_population = selection(new_population);
			new_population.clear();
			crossover(current_population, new_population);
			current_population.clear();
			mutation(new_population);
			refreshFitness(new_population);
		}
		std::cout << "\n\n" << "BEST PATH:";
		test->getBestRoute()->printRouting(m_problem->getDepot());
		experiment->addTest(test);
	}
	std::cout << "\nCOMPLETED\n";
	return experiment->getOverallSummary();
}

std::vector<Individual*> Evolution::createPopulation() {
	std::vector<Individual*> population;
	Location* depot = m_problem->getDepot();
	std::vector<Location*> locations = m_problem->getLocations();
	int capacity = m_problem->getCapacity();
	int dimension = m_problem->getDimension();
	for(int i = 0; i < m_config->getPopSize(); i++) {
		Individual* individual = new Individual(dimension);
		individual->setRandomGenotype(depot, locations, capacity);
		individual->countFitness(depot, locations);
		population.push_back(individual);
	}
	return population;
}

void Evolution::mutation(std::vector<Individual*> t_population) {
	Location* depot = m_problem->getDepot();
	std::vector<Location*> locations = m_problem->getLocations();
	int capacity = m_problem->getCapacity();
	int pop_size = t_population.size();
	for(int i = 0; i < pop_size; i++) {
		Individual* individual = t_population[i];
		int chance = rand() % 100;
		if(chance < m_config->getPM()) {
			individual->mutate(m_config->getMutationType(), depot, locations, capacity);
		}
	}
}

void Evolution::crossover(std::vector<Individual*> t_population, std::vector<Individual*>& t_new_population) {
	Location* depot = m_problem->getDepot();
	std::vector<Location*> locations = m_problem->getLocations();
	int capacity = m_problem->getCapacity();
	for(int i = 0; t_new_population.size() < m_config->getPopSize(); i++) {
		int parent1_id = rand() % m_config->getPopSize();
		int parent2_id = parent1_id;
		while(parent2_id == parent1_id) {
			parent2_id = rand() % m_config->getPopSize();
		}
		Individual* parent1 = t_population[parent1_id];
		Individual* parent2 = t_population[parent2_id];

		int chance = rand() % 100;
		if(chance < m_config->getPX()) {
			std::vector<Individual*> childs;
			childs = parent1->crossover(m_config->getCrossoverType(), depot, locations, capacity, parent2);
			t_new_population.push_back(childs[0]);
			t_new_population.push_back(childs[1]);
		}
		else {
			t_new_population.push_back(new Individual(parent1));
			t_new_population.push_back(new Individual(parent2));
		}
		
	}
}

std::vector<Individual*> Evolution::tournamentSelection(std::vector<Individual*> t_population)
{
	std::vector<Individual*> new_population;
	int rivals_amount = m_config->getPopSize() * (m_config->getTour() / 100);
	if(rivals_amount <= 0) {
		rivals_amount = 1;
	}
	for(int i = 0; i < m_config->getPopSize(); i++) {
		std::vector<int> tournament;
		// select rivals
		for(int r = 0; r < rivals_amount; r++) {
			int index = rand() % t_population.size();
			while(utils::findIndex(tournament, index) != -1) {
				index = rand() % t_population.size();
			}
			tournament.push_back(index);
		}
		// choose winner
		int winner_id = tournament[0];
		double best_fitness = t_population[winner_id]->getFitness();
		for(int r = 0; r < rivals_amount; r++) {
			double fitness = t_population[tournament[r]]->getFitness();
			if(fitness < best_fitness) {
				best_fitness = fitness;
				winner_id = tournament[r];
			}
		}
		new_population.push_back(t_population[winner_id]);
	}
	return new_population;
}

std::vector<Individual*> Evolution::rouletteSelection(std::vector<Individual*> t_population)
{
	std::vector<Individual*> new_population;
	double fitness_population = 0;
	int pop_size = t_population.size();
	for(int i = 0; i < pop_size; i++) {
		fitness_population += t_population[i]->getFitness();
	}
	std::vector<double> chances;
	double previous_chance = 0;
	for(int i = 0; i < pop_size; i++) {
		double fitness = t_population[i]->getFitness();
		double chance = ((fitness_population - fitness) * fitness) / pow(fitness_population, 2) + previous_chance;
		chances.push_back(chance);
		previous_chance = chance;
	}
	for(int i = 0; i < m_config->getPopSize(); i++) {
		double roulette = ((double)rand() / RAND_MAX);
		int winner_id = -1;
		for(int j = 0; j < chances.size(); j++) {
			if(chances[j] > roulette) {
				winner_id = j;
				break;
			}
		}
		if(winner_id == -1) {
			winner_id = rand() % pop_size;
		}
		new_population.push_back(t_population[winner_id]);
	}
	return new_population;
}

std::vector<Individual*>Evolution::selection(std::vector<Individual*> t_population)
{
	switch(m_config->getSelectionType())
	{
		case SelectionType::TOURNAMENT:
			return tournamentSelection(t_population);
		case SelectionType::ROULETTE:
			return rouletteSelection(t_population);
		default:
			break;
	}
}

void Evolution::refreshFitness(std::vector<Individual*> t_population)
{
	int pop_size = t_population.size();
	Location* depot = m_problem->getDepot();
	std::vector<Location*> locations = m_problem->getLocations();
	for(int i = 0; i < pop_size; i++) {
		t_population[i]->countFitness(depot, locations);
	}
}
