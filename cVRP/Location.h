#pragma once
#include "NodeCoord.h"
class Location
{
	public:
		Location(int id, NodeCoord* t_coords);
		void setDemands(int t_demand_resource);
		int getDemands();
		NodeCoord* getCoords();
		int getId();
		double countDistance(NodeCoord* t_coords);
	private:
		int m_id = 0;
		NodeCoord* m_coords = nullptr;
		int m_resource_demand;
};

