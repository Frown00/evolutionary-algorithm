#include "VehicleRoutingProblem.h"

VehicleRoutingProblem::VehicleRoutingProblem()
{
	this->m_locations = std::vector<Location*>();
}

void VehicleRoutingProblem::addLocation(Location* t_loc)
{
	m_locations.push_back(t_loc);
}

void VehicleRoutingProblem::setDepot(Location* t_depot)
{
	this->m_depot = t_depot;
}

Location* VehicleRoutingProblem::getDepot() {
	return m_depot;
}

void VehicleRoutingProblem::setName(std::string t_name)
{
	this->m_name = t_name;
}

void VehicleRoutingProblem::setType(std::string t_type)
{
	this->m_type = t_type;
}

void VehicleRoutingProblem::setComment(std::string t_comment)
{
	this->m_comment = t_comment;
}

void VehicleRoutingProblem::setDimension(int t_dimension)
{
	this->m_dimension = t_dimension;
}

void VehicleRoutingProblem::setEdgeWeightType(std::string t_edge_weight)
{
	this->m_edge_weight_type = t_edge_weight;
}

void VehicleRoutingProblem::setCapacity(int t_capacity)
{
	this->m_capacity = t_capacity;
}

int VehicleRoutingProblem::getCapacity() {
	return m_capacity;
}

int VehicleRoutingProblem::getDimension() {
	return m_dimension;
}

std::vector<Location*> VehicleRoutingProblem::getLocations()
{
	return m_locations;
}
