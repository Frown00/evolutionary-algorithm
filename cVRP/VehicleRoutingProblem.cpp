#include "VehicleRoutingProblem.h"

VehicleRoutingProblem::VehicleRoutingProblem()
{
	this->locations = std::vector<Location*>();
}

void VehicleRoutingProblem::addLocation(Location* t_loc)
{
	locations.push_back(t_loc);
}

void VehicleRoutingProblem::setDepot(Location* t_depot)
{
	this->depot = t_depot;
}

void VehicleRoutingProblem::setName(std::string t_name)
{
	this->name = t_name;
}

void VehicleRoutingProblem::setType(std::string t_type)
{
	this->type = t_type;
}

void VehicleRoutingProblem::setComment(std::string t_comment)
{
	this->comment = t_comment;
}

void VehicleRoutingProblem::setDimension(int t_dimension)
{
	this->dimension = t_dimension;
}

void VehicleRoutingProblem::setEdgeWeightType(std::string t_edge_weight)
{
	this->edge_weight_type = t_edge_weight;
}

void VehicleRoutingProblem::setCapacity(int t_capacity)
{
	this->capacity = t_capacity;
}

std::vector<Location*> VehicleRoutingProblem::getLocations()
{
	return locations;
}
