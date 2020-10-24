#pragma once
#include <iostream>
#include <fstream>
#include "VehicleRoutingProblem.h"
#include "ErrorMessages.h"
#include "Config.h"

class Loader
{
	public:
		Loader();
		void readFile();
		VehicleRoutingProblem* getProblem();

	private:
		const int NAME_LINE = 0;
		const int COMMENT_LINE = 1;
		const int TYPE_LINE = 2;
		const int DIMENSION_LINE = 3;
		const int EDGE_WEIGHT_LINE = 4;
		const int CAPACITY_LINE = 5;
		const std::string NODE_CONTROL_WORD = "NODE_COORD_SECTION";
		const std::string DEMAND_CONTROL_WORD = "DEMAND_SECTION";
		const std::string DEPOT_CONTROL_WORD = "DEPOT_SECTION";
		void addLocations(VehicleRoutingProblem* vrp);
		void setDemands(VehicleRoutingProblem* vrp);
		void setDepot(VehicleRoutingProblem* vrp);
		std::vector<std::string> lines;
};

