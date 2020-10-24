#pragma once
#include <vector>
#include "Individual.h"
#include "Location.h"
#include "VehicleRoutingProblem.h"
#include "Config.h"

class Evolution {
	public:
		Evolution(VehicleRoutingProblem* t_problem);
		void createPopulation();

	private:
		VehicleRoutingProblem* m_problem;
		std::vector<Individual*> m_population;

};

