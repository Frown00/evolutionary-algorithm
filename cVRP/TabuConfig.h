#pragma once
#include "Configuration.h"
#include "DefaultConfig.h"

class TabuConfig : public Configuration
{
	public:
		TabuConfig();
		void setNeighbours(int t_neighbours);
		void setIterations(int t_iterations);
		void setTabuSize(int t_tabu_size);
		int getNeighbours();
		int getIterations();
		int getTabuSize();
		MutationType getNeighbourhoodType();

	private:
		int m_neighbours;
		int m_iterations;
		int m_tabu_size;
		MutationType m_neighbourhood_type;

};

