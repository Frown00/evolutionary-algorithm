#include "Individual.h"
#include "Config.h"

Individual::Individual(int t_dimension) {
  m_dimension = t_dimension;
  m_fitness = -1;
}

std::vector<int> Individual::getGenotype() {
    return m_genotype;
}

std::vector<int> Individual::getIds(int t_dimension, int t_depot_id) {
  std::vector<int> left_location_ids;
  for(int i = 1; i <= t_dimension; i++) {
    if(i != t_depot_id)
      left_location_ids.push_back(i);
  }
  return left_location_ids;
}

void Individual::setRandomGenotype(Location* t_depot, std::vector<Location*> t_locations, int t_capacity) {
  int dimension = t_locations.size();
  int depotId = t_depot->getId();
  std::vector<int> left_location_ids = getIds(dimension, depotId);
  m_genotype.push_back(t_depot->getId());
  for(int i = 0; i < dimension - 1; i++) {
    int idx = rand() % left_location_ids.size();
    m_genotype.push_back(left_location_ids[idx]);
    left_location_ids.erase(left_location_ids.begin() + idx);
  }
  m_genotype.push_back(t_depot->getId());
  // fill with random returns to depot
  for(int i = 0; i < m_dimension; i++) {
    int idx = rand() % m_genotype.size();
    m_genotype.insert(m_genotype.begin() + idx, t_depot->getId());
  }
  fixGenotype(t_depot, t_locations, t_capacity);
}

double Individual::countFitness(Location* t_depot, std::vector<Location*> t_locations) {
  m_fitness = 0;
  Location* depot = getLocationById(t_locations, t_depot->getId());
  Location* first = getLocationById(t_locations, m_genotype[0]);
  Location* last = getLocationById(t_locations, m_genotype[m_genotype.size() - 1]);
  m_fitness += depot->countDistance(first->getCoords());
  for(int i = 0; i < m_genotype.size() - 1; i++) {
    Location* start_route = getLocationById(t_locations, m_genotype[i]);
    Location* end_route = getLocationById(t_locations, m_genotype[i + 1]);
    m_fitness += start_route->countDistance(end_route->getCoords());
  }
  m_fitness += depot->countDistance(last->getCoords());
  return m_fitness;
}

double Individual::getFitness() {
  return m_fitness;
}

Individual* Individual::crossing(Individual* t_other_individual) {
  return nullptr;
}

Location* Individual::getLocationById(std::vector<Location*> t_locations, int t_id) {
  for(int i = 0; i < t_locations.size(); i++) {
    if(t_locations[i]->getId() == t_id)
      return t_locations[i];
  }
}

void Individual::fixGenotype(Location* t_depot, std::vector<Location*> t_locations, int t_capacity) {
  for(int i = 0; i < m_genotype.size() - 1; i++) {
    if(m_genotype[i] == m_genotype[i + 1]) {
      m_genotype.erase(m_genotype.begin() + i);
      i--;
    }
  }
  int current_weight = 0;
  for(int i = 0; i < m_genotype.size(); i++) {
    if(m_genotype[i] == t_depot->getId()) {
      current_weight = 0;
    }
    else {
      Location* loc = getLocationById(t_locations, m_genotype[i]);
      current_weight += loc->getDemands();
      if(current_weight > t_capacity) {
        m_genotype.insert(m_genotype.begin() + i, t_depot->getId());
        current_weight = 0;
      }
    }
  }
}

void Individual::swapMutation(int t_gen1_pos, int t_gen2_pos) {
  int temp = m_genotype[t_gen1_pos];
  m_genotype[t_gen1_pos] = m_genotype[t_gen2_pos];
  m_genotype[t_gen2_pos] = temp;
}

void Individual::inversionMutation(int t_gen1_pos, int t_gen2_pos) {
  int swap_amount = (abs(t_gen1_pos - t_gen2_pos) + 1)/ 2;
  int left = t_gen1_pos;
  int right = t_gen2_pos;
  if(t_gen1_pos > t_gen2_pos) {
    left = t_gen2_pos;
    right = t_gen1_pos;
  }
  for(int i = 0; i <= swap_amount; i++) {
    swapMutation(left + i, right - i);
  }
}

void Individual::mutate(Location* t_depot, std::vector<Location*> t_locations, int t_capacity) {
  int gen1_id = rand() % m_genotype.size();
  int gen2_id = rand() % m_genotype.size();
  switch(config::MUTATION_TYPE) {
    case evolution::MutationType::SWAP: {
      swapMutation(gen1_id, gen2_id);
      break;
    }
    case evolution::MutationType::INVERSION: {
      inversionMutation(gen1_id, gen2_id);
      break;
    }
    default: break;
  }
  fixGenotype(t_depot, t_locations, t_capacity);
}

void Individual::printRouting(Location* t_depot) {
  int route = 1;
  std::cout << "\nDEPOT ID: " << t_depot->getId();
  for(int i = 0; i < m_genotype.size() - 1; i++) {
    if(m_genotype[i] == t_depot->getId()) {
      std::cout << "\nROUTE " + std::to_string(route) + ": ";
      route++;
    }
    else {
      std::cout << m_genotype[i];
      if(m_genotype[i + 1] != t_depot->getId()) {
        std::cout << " -> ";
      }
    }
  }
  std::cout << '\n' << "FITNESS: " << m_fitness;
}
