#pragma once
#include "NodeCoord.h"
class Location
{
	public:
		Location(NodeCoord* t_coords);
		void setDemands(int t_demand_resource);
	private:
		NodeCoord* coords = nullptr;
		int resource_demand;
};

