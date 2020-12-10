#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Location.h"
#include "Enums.h"
class Individual {
	public:
		Individual(int t_dimension);
		Individual(Individual* other);
		~Individual();
		std::vector<int> getGenotype();
		std::string getTextGenotype();
		void setGenotype(std::vector<int> t_genotype);
		std::vector<int> getPlainGenotype(Location* t_depot); // without returns to depot station
		void setRandomGenotype(Location* t_depot, std::vector<Location*> t_locations, int t_capacity);
		double countFitness(Location* t_depot, std::vector<Location*> t_locations);
		double getFitness();
		std::vector<Individual*> crossover(
			CrossoverType t_type,
			Location* t_depot, 
			std::vector<Location*> t_locations, 
			int t_capacity, 
			Individual* t_other_individual
		);
		
		void mutate(
			MutationType t_type,
			Location* t_depot, 
			std::vector<Location*> t_locations, 
			int t_capacity
		);
		void fixGenotype(Location* t_depot, std::vector<Location*> t_locations, int t_capacity);
		void printRouting(Location* t_depot);
	private:
		
		Location* getLocationById(std::vector<Location*> t_locations, int t_id);
		void swapMutation(int t_gen1_pos, int t_gen2_pos);
		void inversionMutation(int t_gen1_pos, int t_gen2_pos);
		std::vector<std::vector<int>> cycleCrossover(Individual* t_other_individual, Location* t_depot);
		std::vector<std::vector<int>> orderedCrossover(Individual* t_other_individual, Location* t_depot);
		std::vector<int> getIds(int t_dimension, int t_depot_id);
		std::vector<int> m_genotype;
		std::string m_genotype_text;
		int m_dimension;
		double m_fitness;

};

