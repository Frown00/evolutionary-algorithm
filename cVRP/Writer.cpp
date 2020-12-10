#include "Writer.h"

void Writer::openEvolutionFile(EvolutionConfig* t_config)
{
	std::string mutation_name = "";
	std::string mutation_type = "";
	std::string crossover_name = "";
	std::string crossover_type = "";
	std::string selection_name = "";
	std::string selection_type = "";

	switch(t_config->getMutationType()) {
		case MutationType::SWAP:
			mutation_name = "S_PM";
			mutation_type = "SWAP";
			break;
		case MutationType::INVERSION:
			mutation_name = "I_PM";
			mutation_type = "INVERSION";
			break;
		}
	switch(t_config->getCrossoverType()) {
		case CrossoverType::ORDERED:
			crossover_name = "O_PX";
			crossover_type = "ORDERED";
			break;
		case CrossoverType::CYCLE:
			crossover_name = "C_PX";
			crossover_type = "CYCLE";
			break;
		}
	switch(t_config->getSelectionType()) {
		case SelectionType::TOURNAMENT:
			selection_name = "T" + std::to_string(t_config->getTour());
			selection_type = "TOURNAMENT";
			break;
		case SelectionType::ROULETTE:
			selection_name = "R";
			selection_type = "ROULETTE";
			break;
		}
	std::string filename = t_config->getInstanceProblem() + "-"
		"POP" + std::to_string(t_config->getPopSize()) + "-" +
		"GEN" + std::to_string(t_config->getGenerations()) + "-" +
		crossover_name + std::to_string((int)t_config->getPX()) + "-" +
		mutation_name + std::to_string((int)t_config->getPM()) + "-" +
		selection_name;
	m_file.open("./results/" + filename + ".csv");

	m_file << "Constrained vehicle routing problem\n";
	m_file << "Instance name: " + t_config->getInstanceProblem() + "\n";
	m_file << "Evolution parameters\n";
	m_file << "Population size:;" + std::to_string(t_config->getPopSize()) + "\n";
	m_file << "Generation number:;" + std::to_string(t_config->getGenerations()) + "\n";
	m_file << "Mutation type:;" + mutation_type + "; Probability: " + std::to_string(t_config->getPM()) + "\n";
	m_file << "Crossover type:;" + crossover_type + "; Probability: " + std::to_string(t_config->getPX()) + "\n";
	m_file << "Selection type:;" + selection_type;
	if(t_config->getSelectionType() == SelectionType::TOURNAMENT) {
		m_file << ";Parameter: " + std::to_string(t_config->getTour()) + "\n";
	}
	else {
		m_file << "\n";
	}
}

void Writer::openTabuFile(TabuConfig* t_config)
{
	std::string mutation_name = "";
	std::string mutation_type = "";
	switch (t_config->getNeighbourhoodType()) {
		case MutationType::SWAP:
			mutation_name = "SWAP";
			mutation_type = "SWAP";
			break;
		case MutationType::INVERSION:
			mutation_name = "INVERSION";
			mutation_type = "INVERSION";
			break;
		}
	std::string filename = t_config->getInstanceProblem() + "-tabu_search-" +
		"ITER" + std::to_string(t_config->getIterations()) + "-" +
		"N" + std::to_string(t_config->getNeighbours()) + "-" +
		"TS" + std::to_string(t_config->getTabuSize()) + "-" +
		mutation_name;
	m_file.open("./results/" + filename + ".csv");
	m_file << "Constrained vehicle routing problem\n";
	m_file << "Instance name: " + t_config->getInstanceProblem() + "\n";
	m_file << "Tabu search parameters\n";
	m_file << "Iterations:;" + std::to_string(t_config->getIterations()) + "\n";
	m_file << "Neighbours:;" + std::to_string(t_config->getNeighbours()) + "\n";
	m_file << "Tabu size:;" + std::to_string(t_config->getTabuSize()) + "\n";
	m_file << "Neighbour operation:;" + mutation_type + "\n";
}

void Writer::openAnealingFile(SAConfig* t_config)
{
	std::string mutation_name = "";
	std::string mutation_type = "";
	switch (t_config->getNeighbourhoodType()) {
	case MutationType::SWAP:
		mutation_name = "SWAP";
		mutation_type = "SWAP";
		break;
	case MutationType::INVERSION:
		mutation_name = "INVERSION";
		mutation_type = "INVERSION";
		break;
	}
	std::string filename = t_config->getInstanceProblem() + "-annealing-" +
		"ITER" + std::to_string(t_config->getIterations()) + "-" +
		"N" + std::to_string(t_config->getNeighbours()) + "-" +
		"T_START" + std::to_string(t_config->getTempStart()) + "-" +
		"T_STOP" + std::to_string(t_config->getTempStop()) + "-" +
		"C_R" + std::to_string(t_config->getCoolingRate()) + "-" +
		mutation_name;
	m_file.open("./results/" + filename + ".csv");
	m_file << "Constrained vehicle routing problem\n";
	m_file << "Instance name: " + t_config->getInstanceProblem() + "\n";
	m_file << "Simulated annealing parameters\n";
	m_file << "Iterations:;" + std::to_string(t_config->getIterations()) + "\n";
	m_file << "Neighbours:;" + std::to_string(t_config->getNeighbours()) + "\n";
	m_file << "Temperature start:;" + std::to_string(t_config->getTempStart()) + "\n";
	m_file << "Temperature stop:;" + std::to_string(t_config->getTempStop()) + "\n";
	m_file << "Cooling rate:;" + std::to_string(t_config->getCoolingRate()) + "\n";
	m_file << "Neighbour operation:;" + mutation_type + "\n";
}

void Writer::openOverallFile(std::string name)
{
	m_file.open("./overall/" + name + ".csv");
	m_file << "Constrained vehicle routing problem\n";
	m_file << "File name: " + name + "\n";
}

void Writer::saveOverall(std::vector<std::string> problems, std::vector<Summary*> t_overall)
{
	m_file << "Instance;Best;Worst;Average;Std\n";
	for (int i = 0; i < problems.size(); i++) {
		m_file << problems[i] + ";" +
			std::to_string(t_overall[i]->getBest()) + ";" +
			std::to_string(t_overall[i]->getWorst()) + ";" +
			std::to_string(t_overall[i]->getAverage()) + ";" +
			std::to_string(t_overall[i]->getStd()) + "\n";
	}
	
}

void Writer::saveGreedy(Summary* t_greedy)
{
	m_file << "\nGreedy solution\n";
	m_file << "Best;Worst;Average;Std\n";
	m_file << std::to_string(t_greedy->getBest()) + ";" +
		std::to_string(t_greedy->getWorst()) + ";" +
		std::to_string(t_greedy->getAverage()) + ";" +
		std::to_string(t_greedy->getStd()) + "\n";
}

void Writer::saveRandom(Summary* t_random)
{
	m_file << "\nRandom solution\n";
	m_file << "Best;Worst;Average;Std\n";
	m_file << std::to_string(t_random->getBest()) + ";" +
		std::to_string(t_random->getWorst()) + ";" +
		std::to_string(t_random->getAverage()) + ";" +
		std::to_string(t_random->getStd()) + "\n";
	
}

void Writer::saveEvolution(Test* t_evolution)
{
	m_file << "\nEvolution solution\n";
	m_file << "Generation;Best;Worst;Average;Best Ever;Std\n";
	std::vector<Summary*> generations = t_evolution->getSummaries();
	double best_ever = generations[0]->getBest();
	for(int g = 0; g < generations.size(); g++) {
		if(generations[g]->getBest() < best_ever)
			best_ever = generations[g]->getBest();
		m_file <<
			std::to_string(g) + ";" +
			std::to_string(generations[g]->getBest()) + ";" +
			std::to_string(generations[g]->getWorst()) + ";" +
			std::to_string(generations[g]->getAverage()) + ";" +
			std::to_string(best_ever) + ";" +
			std::to_string(generations[g]->getStd()) + "\n";
	}
}

void Writer::saveTabu(Test* t_tabu)
{
	std::vector<Summary*> iterations = t_tabu->getSummaries();
	m_file << "\nTabu search solution\n";
	m_file << "Iteration;Best;Worst;Average;Best Ever;Std\n";
	double best_ever = iterations[0]->getBest();
	for (int i = 0; i < iterations.size(); i+=2) {
		if (iterations[i]->getBest() < best_ever)
			best_ever = iterations[i]->getBest();
		m_file <<
			std::to_string(i) + ";" +
			std::to_string(iterations[i]->getBest()) + ";" +
			std::to_string(iterations[i]->getWorst()) + ";" +
			std::to_string(iterations[i]->getAverage()) + ";" +
			std::to_string(best_ever) + ";" +
			std::to_string(iterations[i]->getStd()) + "\n";
	}
}

void Writer::saveAnealing(Test* t_anealing)
{
	std::vector<Summary*> iterations = t_anealing->getSummaries();
	m_file << "\nSimulated annealing solution\n";
	m_file << "Iteration;Best;Best Ever;Std\n";
	double best_ever = iterations[0]->getBest();
	for (int i = 0; i < iterations.size(); i+=100) {
		if(iterations[i]->getBest() < best_ever)
			best_ever = iterations[i]->getBest();
		m_file <<
			std::to_string(i) + ";" +
			std::to_string(iterations[i]->getBest()) + ";" +
			/*std::to_string(t_anealing[i]->getWorst()) + ";" +
			std::to_string(t_anealing[i]->getAverage()) + ";" +*/
			std::to_string(best_ever) + "\n";
			//std::to_string(t_anealing[i]->getStd()) + "\n";
	}
}

void Writer::close()
{
	m_file.close();
}
