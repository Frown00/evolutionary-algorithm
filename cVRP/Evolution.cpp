
#include "Evolution.h"
#include "Config.h"

using namespace evolution;

Evolution::Evolution(VehicleRoutingProblem* t_problem) {
	m_problem = t_problem;
}

void Evolution::solve() {
	createPopulation();
	mutation();
	crossover();
	refreshFitness();
	selection();
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
	for(int i = 0; i < config::POP_SIZE; i++) {
		int parent1_id = rand() % config::POP_SIZE;
		int parent2_id = parent1_id;
		while(parent2_id == parent1_id) {
			parent2_id = rand() % config::POP_SIZE;
		}
		Individual* parent1 = m_population[parent1_id];
		Individual* parent2 = m_population[parent2_id];

		int chance = rand() % 100;
		if(chance < config::P_X) {
			std::vector<Individual*> childs;
			childs = parent1->crossover(
				m_problem->getDepot(),
				m_problem->getLocations(),
				m_problem->getCapacity(),
				parent2
			);
			m_population.push_back(childs[0]);
			m_population.push_back(childs[1]);
		}
	}
}

void evolution::Evolution::tournamentSelection()
{
	std::vector<Individual*> new_population;
	int rivals_amount = m_population.size() * (config::TOUR / 100);
	for(int i = 0; i < config::POP_SIZE; i++) {
		std::vector<int> tournament;
		// select rivals
		for(int r = 0; r < rivals_amount; r++) {
			int index = rand() % m_population.size();
			while(utils::find_index(tournament, index) != -1) {
				index = rand() % m_population.size();
			}
			tournament.push_back(index);
		}
		// choose winner
		int winner_id = tournament[0];
		int best_fitness = m_population[tournament[0]]->getFitness();
		for(int r = 0; r < tournament.size(); r++) {
			int fitness = m_population[tournament[r]]->getFitness();
			if(fitness < best_fitness) {
				best_fitness = fitness;
				winner_id = tournament[r];
			}
		}
		new_population.push_back(m_population[winner_id]);
	}
	m_population = new_population;
}

void evolution::Evolution::rouletteSelection()
{
	std::vector<Individual*> new_population;
	double fitness_population = 0;
	for(int i = 0; i < m_population.size(); i++) {
		fitness_population += m_population[i]->getFitness();
	}
	std::vector<double> chances;
	double previous_chance = 0;
	for(int i = 0; i < m_population.size(); i++) {
		double fitness = m_population[i]->getFitness();
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
			winner_id = rand() % m_population.size();
		}
		new_population.push_back(m_population[winner_id]);
	}
	m_population = new_population;
}

void evolution::Evolution::selection()
{
	switch(config::SELECTION_TYPE)
	{
		case SelectionType::TOURNAMENT:
			tournamentSelection();
			break;
		case SelectionType::ROULETTE:
			rouletteSelection();
			break;
	default:
		break;
	}
}

void evolution::Evolution::refreshFitness()
{
	for(int i = 0; i < m_population.size(); i++) {
		m_population[i]->countFitness(m_problem->getDepot(), m_problem->getLocations());
	}
}
