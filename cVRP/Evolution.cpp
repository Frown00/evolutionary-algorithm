
#include "Evolution.h"
#include "Config.h"
#include <fstream>
#include <string> 

using namespace evolution;

Evolution::Evolution(VehicleRoutingProblem* t_problem) {
	m_problem = t_problem;
}

Test* evolution::Evolution::solve()
{
	Test* test = new Test(0);
	std::cout << "\nEVOLUTION" << "\n";
	std::vector<Individual*> new_population = createPopulation();
	for (int g = 1; g <= config::GEN; g++) {
		Summary* generation_summary = new Summary(g);
		std::cout << "\r" << "EVOLUTION PROGRESS: " << g << " / " << config::GEN;
		for (int i = 0; i < new_population.size(); i++) {
			generation_summary->addResult(new_population[i]);
		}
		generation_summary->countAverage();
		generation_summary->countStd();
		test->addSummary(generation_summary);
		std::vector<Individual*> current_population = selection(new_population);
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
		for(int g = 1; g <= config::GEN; g++) {
			Summary* generation_summary = new Summary(g);
			std::cout << "\r" << "EVOLUTION PROGRESS: " << g << " / " << config::GEN;
			for(int i = 0; i < new_population.size(); i++) {
				generation_summary->addResult(new_population[i]);
			}
			generation_summary->countAverage();
			test->addSummary(generation_summary);
			std::vector<Individual*> current_population = selection(new_population);
			new_population.clear();
			crossover(current_population, new_population);
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
	for(int i = 0; i < config::POP_SIZE; i++) {
		Individual* individual = new Individual(m_problem->getDimension());
		individual->setRandomGenotype(
			m_problem->getDepot(),
			m_problem->getLocations(),
			m_problem->getCapacity()
		);
		individual->countFitness(m_problem->getDepot(), m_problem->getLocations());
		population.push_back(individual);
	}
	return population;
}

void Evolution::mutation(std::vector<Individual*> t_population) {
	for(int i = 0; i < t_population.size(); i++) {
		Individual* individual = t_population[i];
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

void Evolution::crossover(std::vector<Individual*> t_population, std::vector<Individual*>& t_new_population) {
	for(int i = 0; i < config::POP_SIZE; i++) {
		int parent1_id = rand() % config::POP_SIZE;
		int parent2_id = parent1_id;
		while(parent2_id == parent1_id) {
			parent2_id = rand() % config::POP_SIZE;
		}
		Individual* parent1 = t_population[parent1_id];
		Individual* parent2 = t_population[parent2_id];

		int chance = rand() % 100;
		if(chance < config::P_X) {
			std::vector<Individual*> childs;
			childs = parent1->crossover(
				m_problem->getDepot(),
				m_problem->getLocations(),
				m_problem->getCapacity(),
				parent2
			);
			t_new_population.push_back(childs[0]);
			t_new_population.push_back(childs[1]);
		}
		
	}
}

std::vector<Individual*> evolution::Evolution::tournamentSelection(std::vector<Individual*> t_population)
{
	std::vector<Individual*> new_population;
	int rivals_amount = t_population.size() * (config::TOUR / 100);
	if(rivals_amount <= 0) {
		rivals_amount = 1;
	}
	for(int i = 0; i < config::POP_SIZE; i++) {
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
		double best_fitness = t_population[tournament[0]]->getFitness();
		for(int r = 0; r < tournament.size(); r++) {
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

std::vector<Individual*> evolution::Evolution::rouletteSelection(std::vector<Individual*> t_population)
{
	std::vector<Individual*> new_population;
	double fitness_population = 0;
	for(int i = 0; i < t_population.size(); i++) {
		fitness_population += t_population[i]->getFitness();
	}
	std::vector<double> chances;
	double previous_chance = 0;
	for(int i = 0; i < t_population.size(); i++) {
		double fitness = t_population[i]->getFitness();
		double chance = ((fitness_population - fitness) * fitness) / pow(fitness_population, 2) + previous_chance;
		chances.push_back(chance);
		previous_chance = chance;
	}
	for(int i = 0; i < config::POP_SIZE; i++) {
		double roulette = ((double)rand() / RAND_MAX);
		int winner_id = -1;
		for(int j = 0; j < chances.size(); j++) {
			if(chances[j] > roulette) {
				winner_id = j;
				break;
			}
		}
		if(winner_id == -1) {
			winner_id = rand() % t_population.size();
		}
		new_population.push_back(t_population[winner_id]);
	}
	return new_population;
}

std::vector<Individual*> evolution::Evolution::selection(std::vector<Individual*> t_population)
{
	switch(config::SELECTION_TYPE)
	{
		case SelectionType::TOURNAMENT:
			return tournamentSelection(t_population);
		case SelectionType::ROULETTE:
			return rouletteSelection(t_population);
		default:
			break;
	}
}

void evolution::Evolution::refreshFitness(std::vector<Individual*> t_population)
{
	for(int i = 0; i < t_population.size(); i++) {
		t_population[i]->countFitness(m_problem->getDepot(), m_problem->getLocations());
	}
}
