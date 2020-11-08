#pragma once
#include "NodeCoord.h"
#include "Location.h"
#include "utils.cpp"
#include "Individual.h"
#include "Summary.h"

class VehicleRoutingProblem
{
	public:
		VehicleRoutingProblem();
		void addLocation(Location* t_loc);
		void setDepot(Location* t_depot);
		Location* getDepot();
		void setName(std::string t_name);
		void setType(std::string t_type);
		void setComment(std::string t_comment);
		void setDimension(int t_dimension);
		void setEdgeWeightType(std::string t_edge_weight);
		void setCapacity(int t_capacity);
		int getCapacity();
		int getDimension();
		std::vector<Location*> getLocations();
		Summary* greedySolution();
		double greedyAlghorithm(int depotId);
		Summary* randomSolution(int attempts);
		double randomSolver();
	private:
		std::string m_name = "";
		std::string m_type = "";
		std::string m_comment = "";
		int m_dimension = 0;
		std::string m_edge_weight_type = "";
		int m_capacity = 0;
		std::vector<Location*> m_locations = std::vector<Location*>();
		Location* m_depot = nullptr;
		std::vector<int> getLocationsIds(Location* t_depot);
		Location* getLocationById(int t_id);
};

