
#include "Evolution.h"
#include "Config.h"
#include <fstream>
#include <string> 

using namespace evolution;

Evolution::Evolution(VehicleRoutingProblem* t_problem) {
	m_problem = t_problem;
}

void Evolution::solve(int t_test_num) {
	createPopulation();
	std::vector<std::vector<Summary*>> test_summary;
	for(int t = 0; t < t_test_num; t++) {
		std::cout << "EVOLUTION TEST: " << t + 1 << "\n";
		std::vector<Summary*> generation_summaries;
		for (int g = 1; g <= config::GEN; g++) {
			std::cout << "\r" << "EVOLUTION PROGRESS: " << g << " / " << config::GEN;
			Summary* summary = new Summary();
			for (int i = 0; i < m_population.size(); i++) {
				summary->addResult(stoi(std::to_string(g) + std::to_string(i)), m_population[i]->getFitness());
			}
			summary->countAverage();
			summary->countStd();
			generation_summaries.push_back(summary);
			mutation();
			crossover();
			refreshFitness();
			selection();
		}
		std::cout << "\nCOMPLETED\n";
		test_summary.push_back(generation_summaries);
	}
	for(int g = 0; g < config::GEN; g++) {
		Summary* overall = new Summary();
		for(int j = 0; j < config::POP_SIZE; j++) {
			double sum = 0;
			for(int t = 0; t < test_summary.size(); t++) {
				Summary* summary = test_summary[t][g];
				sum += summary->getResult(j);
			}
			overall->addResult(0, sum / t_test_num);
		}
		overall->countAverage();
		overall->countStd();
		m_test_summaries.push_back(overall);
	}
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

void evolution::Evolution::saveResults(Summary* t_greedy, Summary* t_random)
{
	std::ofstream myfile;
	std::string mutation_name = "";
	std::string mutation_type = "";
	std::string crossover_name = "";
	std::string crossover_type = "";
	std::string selection_name = "";
	std::string selection_type = "";

	switch (config::MUTATION_TYPE) {
	case evolution::MutationType::SWAP:
		mutation_name = "S_PM";
		mutation_type = "SWAP";
		break;
	case evolution::MutationType::INVERSION:
		mutation_name = "I_PM";
		mutation_type = "INVERSION";
		break;
	}
	switch (config::CROSSOVER_TYPE) {
	case evolution::CrossoverType::ORDERED:
		crossover_name = "O_PX";
		crossover_type = "ORDERED";
		break;
	case evolution::CrossoverType::CYCLE:
		crossover_name = "C_PX";
		crossover_type = "CYCLE";
		break;
	}
	switch (config::SELECTION_TYPE) {
	case evolution::SelectionType::TOURNAMENT:
		selection_name = "T" + std::to_string(config::TOUR);
		selection_type = "TOURNAMENT";
		break;
	case evolution::SelectionType::ROULETTE:
		selection_name = "R";
		selection_type = "ROULETTE";
		break;
	}
	std::string filename = config::INSTANCE_PROBLEM + "-"
		"POP" + std::to_string(config::POP_SIZE) + "-" +
		"GEN" + std::to_string(config::GEN) + "-" +
		crossover_name + std::to_string((int)config::P_X) + "-" +
		mutation_name + std::to_string((int)config::P_M) + "-" +
		selection_name;
	myfile.open("./results/" + filename + ".csv");
	myfile << "Constrained vehicle routing problem\n";
	myfile << "Instance name: " + config::INSTANCE_PROBLEM + "\n";
	myfile << "Evolution parameters\n";
	myfile << "Population size:;" + std::to_string(config::POP_SIZE) + "\n";
	myfile << "Generation number:;" + std::to_string(config::GEN) + "\n";
	myfile << "Mutation type:;" + mutation_type + "; Probability: " + std::to_string(config::P_M) + "\n";
	myfile << "Crossover type:;" + crossover_type + "; Probability: " + std::to_string(config::P_X) + "\n";
	myfile << "Selection type:;" + selection_type;
	if (config::SELECTION_TYPE == evolution::SelectionType::TOURNAMENT) {
		myfile << ";Parameter: " + std::to_string(config::TOUR) + "\n";
	}
	else {
		myfile << "\n";
	}
	myfile << "\nGreedy solution\n";
	myfile << "Best;Worst;Average;Std\n";
	myfile << std::to_string(t_greedy->getBest()) + ";" +
		std::to_string(t_greedy->getWorst()) + ";" +
		std::to_string(t_greedy->getAverage()) + ";" +
		std::to_string(t_greedy->getStd()) + "\n";
	myfile << "\nRandom solution\n";
	myfile << "Best;Worst;Average;Std\n";
	myfile << std::to_string(t_random->getBest()) + ";" +
		std::to_string(t_random->getWorst()) + ";" +
		std::to_string(t_random->getAverage()) + ";" +
		std::to_string(t_random->getStd()) + "\n";
	myfile << "\nEvolution solution\n";
	myfile << "Generation;Best;Worst;Average;Std\n";
	for(int g = 0; g < m_test_summaries.size(); g++) {
		myfile << 
			std::to_string(g) + ";" +
			std::to_string(m_test_summaries[g]->getBest()) + ";" +
			std::to_string(m_test_summaries[g]->getWorst()) + ";" +
			std::to_string(m_test_summaries[g]->getAverage()) + ";" +
			std::to_string(m_test_summaries[g]->getStd()) + "\n";
	}
	myfile.close();
}
