#include "Location.h"
#include <cmath>

Location::Location()
{
}

Location::Location(int t_id, NodeCoord* t_coords)
{
	m_id = t_id;
	m_coords = new NodeCoord(t_coords);
	m_resource_demand = 0;
}


void Location::setDemands(int t_demand_resource)
{
	m_resource_demand = t_demand_resource;
}

int Location::getDemands() {
	return m_resource_demand;
}

NodeCoord* Location::getCoords() {
	return m_coords;
}

int Location::getId() {
	return m_id;
}

double Location::countDistance(NodeCoord* t_coords) {
	int target_x = t_coords->getX();
	int target_y = t_coords->getY();
	int origin_x = m_coords->getX();
	int origin_y = m_coords->getY();
	return sqrt(pow(origin_x - target_x, 2) + pow(origin_y - target_y, 2));
}
