#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Location.h"

class Individual {
	public:
		Individual(int t_dimension);
		std::vector<int> getGenotype();
		void setRandomGenotype(Location* t_depot, std::vector<Location*> t_locations, int t_capacity);
		double countFitness(Location* t_depot, std::vector<Location*> t_locations);
		double getFitness();
		Individual* crossing(Individual* t_other_individual);
		void mutate(Location* t_depot, std::vector<Location*> t_locations, int t_capacity);
		void printRouting(Location* t_depot);
	private:
		Location* getLocationById(std::vector<Location*> t_locations, int t_id);
		void fixGenotype(Location* t_depot, std::vector<Location*> t_locations, int t_capacity);
		void swapMutation(int t_gen1_pos, int t_gen2_pos);
		void inversionMutation(int t_gen1_pos, int t_gen2_pos);
		std::vector<int> getIds(int t_dimension, int t_depot_id);
		std::vector<int> m_genotype;
		int m_dimension;
		double m_fitness;

};

