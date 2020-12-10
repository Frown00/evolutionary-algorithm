#pragma once
#include "Configuration.h"
#include "DefaultConfig.h"

class SAConfig : public Configuration
{
	public:
		SAConfig();
		void setNeighbours(int t_neighbours);
		void setIterations(int t_iterations);
		void setTemperature(double t_start, double t_stop, double t_cooling_rate);
		int getNeighbours();
		int getIterations();
		double getTempStart();
		double getTempStop();
		double getCoolingRate();
		MutationType getNeighbourhoodType();
	private:
		int m_neighbours;
		int m_iterations;
		double m_temp_start;
		double m_temp_stop;
		double m_cooling_rate;
		MutationType m_neighbourhood_type;
};

