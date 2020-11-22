#include "Writer.h"

void Writer::openEvolutionFile()
{
	std::string mutation_name = "";
	std::string mutation_type = "";
	std::string crossover_name = "";
	std::string crossover_type = "";
	std::string selection_name = "";
	std::string selection_type = "";

	switch(config::MUTATION_TYPE) {
		case evolution::MutationType::SWAP:
			mutation_name = "S_PM";
			mutation_type = "SWAP";
			break;
		case evolution::MutationType::INVERSION:
			mutation_name = "I_PM";
			mutation_type = "INVERSION";
			break;
		}
	switch(config::CROSSOVER_TYPE) {
		case evolution::CrossoverType::ORDERED:
			crossover_name = "O_PX";
			crossover_type = "ORDERED";
			break;
		case evolution::CrossoverType::CYCLE:
			crossover_name = "C_PX";
			crossover_type = "CYCLE";
			break;
		}
	switch(config::SELECTION_TYPE) {
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
	m_file.open("./results/" + filename + ".csv");

	m_file << "Constrained vehicle routing problem\n";
	m_file << "Instance name: " + config::INSTANCE_PROBLEM + "\n";
	m_file << "Evolution parameters\n";
	m_file << "Population size:;" + std::to_string(config::POP_SIZE) + "\n";
	m_file << "Generation number:;" + std::to_string(config::GEN) + "\n";
	m_file << "Mutation type:;" + mutation_type + "; Probability: " + std::to_string(config::P_M) + "\n";
	m_file << "Crossover type:;" + crossover_type + "; Probability: " + std::to_string(config::P_X) + "\n";
	m_file << "Selection type:;" + selection_type;
	if(config::SELECTION_TYPE == evolution::SelectionType::TOURNAMENT) {
		m_file << ";Parameter: " + std::to_string(config::TOUR) + "\n";
	}
	else {
		m_file << "\n";
	}
}

void Writer::openTabuFile()
{
	std::string mutation_name = "";
	std::string mutation_type = "";
	switch (config::MUTATION_TYPE) {
		case evolution::MutationType::SWAP:
			mutation_name = "SWAP";
			mutation_type = "SWAP";
			break;
		case evolution::MutationType::INVERSION:
			mutation_name = "INVERSION";
			mutation_type = "INVERSION";
			break;
		}
	std::string filename = config::INSTANCE_PROBLEM + "-tabu_search-" +
		"ITER" + std::to_string(config::ITERATIONS) + "-" +
		"N" + std::to_string(config::NEIGHBOURS) + "-" +
		"TS" + std::to_string(config::TABU_SIZE) + "-" +
		mutation_name;
	m_file.open("./results/" + filename + ".csv");
	m_file << "Constrained vehicle routing problem\n";
	m_file << "Instance name: " + config::INSTANCE_PROBLEM + "\n";
	m_file << "Tabu search parameters\n";
	m_file << "Iterations:;" + std::to_string(config::ITERATIONS) + "\n";
	m_file << "Neighbours:;" + std::to_string(config::NEIGHBOURS) + "\n";
	m_file << "Tabu size:;" + std::to_string(config::TABU_SIZE) + "\n";
	m_file << "Neighbour operation:;" + mutation_type + "\n";
}

void Writer::openAnealingFile()
{
	std::string mutation_name = "";
	std::string mutation_type = "";
	switch (config::MUTATION_TYPE) {
	case evolution::MutationType::SWAP:
		mutation_name = "SWAP";
		mutation_type = "SWAP";
		break;
	case evolution::MutationType::INVERSION:
		mutation_name = "INVERSION";
		mutation_type = "INVERSION";
		break;
	}
	std::string filename = config::INSTANCE_PROBLEM + "-annealing-" +
		"ITER" + std::to_string(config::ITERATIONS_SA) + "-" +
		"N" + std::to_string(config::NEIGHBOURS_SA) + "-" +
		"T_START" + std::to_string(config::TEMP_START) + "-" +
		"T_STOP" + std::to_string(config::TEMP_STOP) + "-" +
		"C_R" + std::to_string(config::COOLING_RATE) + "-" +
		mutation_name;
	m_file.open("./results/" + filename + ".csv");
	m_file << "Constrained vehicle routing problem\n";
	m_file << "Instance name: " + config::INSTANCE_PROBLEM + "\n";
	m_file << "Simulated annealing parameters\n";
	m_file << "Iterations:;" + std::to_string(config::ITERATIONS) + "\n";
	m_file << "Neighbours:;" + std::to_string(config::NEIGHBOURS_SA) + "\n";
	m_file << "Temperature start:;" + std::to_string(config::TEMP_START) + "\n";
	m_file << "Temperature stop:;" + std::to_string(config::TEMP_STOP) + "\n";
	m_file << "Cooling rate:;" + std::to_string(config::COOLING_RATE) + "\n";
	m_file << "Neighbour operation:;" + mutation_type + "\n";
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

void Writer::saveTabu(std::vector<Summary*> t_tabu)
{
	m_file << "\nTabu search solution\n";
	m_file << "Iteration;Best;Worst;Average;Best Ever;Std\n";
	double best_ever = t_tabu[0]->getBest();
	for (int i = 0; i < t_tabu.size(); i++) {
		if (t_tabu[i]->getBest() < best_ever)
			best_ever = t_tabu[i]->getBest();
		m_file <<
			std::to_string(i) + ";" +
			std::to_string(t_tabu[i]->getBest()) + ";" +
			std::to_string(t_tabu[i]->getWorst()) + ";" +
			std::to_string(t_tabu[i]->getAverage()) + ";" +
			std::to_string(best_ever) + ";" +
			std::to_string(t_tabu[i]->getStd()) + "\n";
	}
}

void Writer::saveAnealing(Test* t_anealing)
{
	std::vector<Summary*> iterations = t_anealing->getSummaries();
	m_file << "\nSimulated annealing solution\n";
	m_file << "Iteration;Best;Best Ever;Std\n";
	double best_ever = iterations[0]->getBest();
	for (int i = 0; i < iterations.size(); i++) {
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
