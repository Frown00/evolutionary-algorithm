#pragma once
#include <vector>
#include <string>
#include "NodeCoord.h"
#include "Location.h"
#include "utils.cpp"

class VehicleRoutingProblem
{
	public:
		VehicleRoutingProblem();
		void addLocation(Location* t_loc);
		void setDepot(Location* t_depot);
		void setName(std::string t_name);
		void setType(std::string t_type);
		void setComment(std::string t_comment);
		void setDimension(int t_dimension);
		void setEdgeWeightType(std::string t_edge_weight);
		void setCapacity(int t_capacity);
		std::vector<Location*> getLocations();
	private:
		std::string name = "";
		std::string type = "";
		std::string comment = "";
		int dimension = 0;
		std::string edge_weight_type = "";
		int capacity = 0;
		std::vector<Location*> locations;
		Location* depot = nullptr;
};

