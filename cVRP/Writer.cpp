#include "Writer.h"

void Writer::saveResults(
	Summary* t_greedy, 
	Summary* t_random,
	std::vector<Summary*> evolution
)
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
	// labels
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

	// save greedy solution
	myfile << "\nGreedy solution\n";
	myfile << "Best;Worst;Average;Std\n";
	myfile << std::to_string(t_greedy->getBest()) + ";" +
		std::to_string(t_greedy->getWorst()) + ";" +
		std::to_string(t_greedy->getAverage()) + ";" +
		std::to_string(t_greedy->getStd()) + "\n";

	// save random solution
	myfile << "\nRandom solution\n";
	myfile << "Best;Worst;Average;Std\n";
	myfile << std::to_string(t_random->getBest()) + ";" +
		std::to_string(t_random->getWorst()) + ";" +
		std::to_string(t_random->getAverage()) + ";" +
		std::to_string(t_random->getStd()) + "\n";
	myfile << "\nEvolution solution\n";
	myfile << "Generation;Best;Worst;Average;Best Ever;Std\n";

	// save evolution
	double bestEver = evolution[0]->getBest();
	for(int g = 0; g < evolution.size(); g++) {
		if(evolution[g]->getBest() < bestEver)
			bestEver = evolution[g]->getBest();
		myfile <<
			std::to_string(g) + ";" +
			std::to_string(evolution[g]->getBest()) + ";" +
			std::to_string(evolution[g]->getWorst()) + ";" +
			std::to_string(evolution[g]->getAverage()) + ";" +
			std::to_string(bestEver) + ";" +
			std::to_string(evolution[g]->getStd()) + "\n";
	}
	myfile.close();
}
