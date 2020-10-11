#include "Location.h"

Location::Location(NodeCoord* t_coords)
{
	this->coords = new NodeCoord(t_coords);
	this->resource_demand = 0;
}


void Location::setDemands(int t_demand_resource)
{
	this->resource_demand = t_demand_resource;
}
