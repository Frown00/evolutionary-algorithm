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

Summary* VehicleRoutingProblem::greedySolution() {
	Summary* summary = new Summary();
	for(int i = 0; i < m_locations.size(); i++) {
		double greedyResult = greedyAlghorithm(m_locations[i]->getId());
		summary->addResult(m_locations[i]->getId(), greedyResult);
	}
	summary->countAverage();
	summary->countStd();
	return summary;
}

double VehicleRoutingProblem::greedyAlghorithm(int depotId) {
	int current_weight = 0;
	double fitness = 0;
	Location* depot = getLocationById(depotId);
	Location* current_location = depot;
	Location* next_location = nullptr;
	std::vector<int> locations_left = getLocationsIds(depot);
	for(int i = 0; i < m_dimension - 1; i++) {
		double shortest_distanse = INFINITY;
		int shortest = -1;
		next_location = nullptr;

		for(int j = 0; j < locations_left.size(); j++) {
			Location* location = getLocationById(locations_left[j]);
			double distance = current_location->countDistance(location->getCoords());
			bool overweighted = current_weight + location->getDemands() > m_capacity;
			bool shorter_distance = distance < shortest_distanse;
			if(shorter_distance && !overweighted) {
				shortest_distanse = distance;
				shortest = j;
				next_location = location;
			}
		}
		// overweighted
		if(next_location == nullptr) {
			double distance_to_depot = current_location->countDistance(depot->getCoords());
			fitness += distance_to_depot; // return to depot
			current_weight = 0;
			next_location = depot;
			/*std::cout << "\n" << current_location->getId() << " -> " << next_location->getId() << " = ";
			std::cout << distance_to_depot;*/
		}
		else {
			locations_left.erase(locations_left.begin() + shortest);
			fitness += shortest_distanse;
			current_weight += next_location->getDemands();
			/*std::cout << "\n" << current_location->getId() << " -> " << next_location->getId() << " = ";
			std::cout << shortest_distanse << " || " << current_weight << " / " << m_capacity;*/
		}
		current_location = next_location;
	}
	fitness += current_location->countDistance(depot->getCoords());
	return fitness;
}

Summary* VehicleRoutingProblem::randomSolution(int attempts) {
	Summary* summary = new Summary();
	for(int i = 0; i < attempts; i++) {
		double greedyResult = randomSolver();
		summary->addResult(i, greedyResult);
	}
	summary->countAverage();
	summary->countStd();
	return summary;
}

double VehicleRoutingProblem::randomSolver() {
	Individual* individual = new Individual(m_dimension);
	individual->setRandomGenotype(m_depot, m_locations, m_capacity);
	double result = individual->countFitness(m_depot, m_locations);
	return result;
}

std::vector<int> VehicleRoutingProblem::getLocationsIds(Location* t_depot) {
	std::vector<int> left_location_ids = std::vector<int>();
	for(int i = 1; i <= m_dimension; i++) {
		if(i != t_depot->getId())
			left_location_ids.push_back(i);
	}
	return left_location_ids;
}

Location* VehicleRoutingProblem::getLocationById(int t_id) {
	for(int i = 0; i < m_locations.size(); i++) {
		if(m_locations[i]->getId() == t_id)
			return m_locations[i];
	}
}
