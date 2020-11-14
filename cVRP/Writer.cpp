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
	m_file.open("./results/" + filename + ".csv");
}

void Writer::openTabuFile()
{
	std::string filename = "abc";
	m_file.open("./results/" + filename + ".csv");
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
	m_file << "\nEvolution solution\n";
	m_file << "Generation;Best;Worst;Average;Best Ever;Std\n";
}

void Writer::saveEvolution(std::vector<Summary*> t_evolution)
{
	double bestEver = t_evolution[0]->getBest();
	for(int g = 0; g < t_evolution.size(); g++) {
		if(t_evolution[g]->getBest() < bestEver)
			bestEver = t_evolution[g]->getBest();
		m_file <<
			std::to_string(g) + ";" +
			std::to_string(t_evolution[g]->getBest()) + ";" +
			std::to_string(t_evolution[g]->getWorst()) + ";" +
			std::to_string(t_evolution[g]->getAverage()) + ";" +
			std::to_string(bestEver) + ";" +
			std::to_string(t_evolution[g]->getStd()) + "\n";
	}
}

void Writer::saveTabu(std::vector<Summary*> t_tabu)
{
}

void Writer::close()
{
	m_file.close();
}
