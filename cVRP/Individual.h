#pragma once
#include <vector>
#include "Location.h"

class Individual {
	public:
		Individual(int t_dimension);
		std::vector<int> getGenotype();
		void setRandomGenotype(Location* t_depot, std::vector<Location*> t_locations, int t_capacity);
		double countFitness(Location* t_depot, std::vector<Location*> t_locations);
		double getFitness();
		void printRouting(Location* t_depot);
	private:
		Location* getLocationById(std::vector<Location*> t_locations, int t_id);
		void fixGenotype(Location* t_depot, std::vector<Location*> t_locations, int t_capacity);
		std::vector<int> getIds(int t_dimension, int t_depot_id);
		std::vector<int> m_genotype;
		int m_dimension;
		double m_fitness;

};

