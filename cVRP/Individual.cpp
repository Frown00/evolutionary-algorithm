#include "Individual.h"
#include "Config.h"

Individual::Individual(int t_dimension) {
  m_dimension = t_dimension;
  m_fitness = -1;
}

Individual::~Individual()
{
  std::cout << "\nINDIVIDUAL DEST\n";
}

std::vector<int> Individual::getGenotype() {
    return m_genotype;
}

std::string Individual::getTextGenotype()
{
  std::string genotype = "";
  for(int i = 0; i < m_genotype.size(); i++) {
    genotype += std::to_string(m_genotype[i]);
    genotype += " ";
  }
  return genotype;
}

void Individual::setGenotype(std::vector<int> t_genotype) {
  for(int i = 0; i < t_genotype.size(); i++) {
    m_genotype.push_back(t_genotype[i]);
  }
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

Location* Individual::getLocationById(std::vector<Location*> t_locations, int t_id) {
  for(int i = 0; i < t_locations.size(); i++) {
    if(t_locations[i]->getId() == t_id)
      return t_locations[i];
  }
}

void Individual::fixGenotype(Location* t_depot, std::vector<Location*> t_locations, int t_capacity) {
  if(m_genotype[0] != t_depot->getId())
    m_genotype.insert(m_genotype.begin() + 0, t_depot->getId());
  if(m_genotype[m_genotype.size() - 1] != t_depot->getId())
    m_genotype.insert(m_genotype.begin() + m_genotype.size(), t_depot->getId());
  // clear depot after depot
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

std::vector<int> Individual::getPlainGenotype(Location* t_depot) {
  std::vector<int> plain_genotype;
  for(int i = 0; i < m_genotype.size(); i++) {
    if(m_genotype[i] != t_depot->getId()) {
      plain_genotype.push_back(m_genotype[i]);
    }
  }
  return plain_genotype;
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
  int gen1_pos = (rand() % (m_genotype.size() - 1)) + 1;
  int gen2_pos = (rand() % (m_genotype.size() - 1)) + 1;
  switch(config::MUTATION_TYPE) {
    case evolution::MutationType::SWAP: {
      swapMutation(gen1_pos, gen2_pos);
      break;
    }
    case evolution::MutationType::INVERSION: {
      inversionMutation(gen1_pos, gen2_pos);
      break;
    }
    default: break;
  }
  fixGenotype(t_depot, t_locations, t_capacity);
}

std::vector<std::vector<int>> Individual::cycleCrossover(Individual* t_other_individual, Location* t_depot) {
  std::vector<int> cycle;
  std::vector<int> parent1 = getPlainGenotype(t_depot);
  std::vector<int> parent2 = t_other_individual->getPlainGenotype(t_depot);
  std::vector<int> child1_genotype, child2_genotype;
  int pos = 0;
  int first_in_cycle = parent1[0];
  cycle.push_back(first_in_cycle); // first is a depot (start point)
  while(parent1.size() > pos) {
    int index = utils::findIndex(parent2, cycle[pos]);
    int gen = parent1[index];
    if(gen == first_in_cycle) break;
    cycle.push_back(gen);
    pos++;
  }
  // crossover
  for(int i = 0; i < parent1.size(); i++) {
    if(utils::findIndex(cycle, parent1[i]) != -1) {
      child1_genotype.push_back(parent2[i]);
      child2_genotype.push_back(parent1[i]);
    }
    else {
      child1_genotype.push_back(parent1[i]);
      child2_genotype.push_back(parent2[i]);
    }
  }
  // set returns to depot according to their parents
  for(int i = 0; i < m_genotype.size(); i++) {
    if(m_genotype[i] == t_depot->getId()) {
      child1_genotype.insert(child1_genotype.begin() + i, m_genotype[i]);
    }
  }
  std::vector<int> partner_genotype = t_other_individual->getGenotype();
  for(int i = 0; i < partner_genotype.size(); i++) {
    if(partner_genotype[i] == t_depot->getId()) {
      child2_genotype.insert(child2_genotype.begin() + i, partner_genotype[i]);
    }
  }
  return std::vector<std::vector<int>> { child1_genotype, child2_genotype };
}

std::vector<std::vector<int>> Individual::orderedCrossover(Individual* t_other_individual, Location* t_depot) {
  std::vector<int> parent1 = getPlainGenotype(t_depot);
  std::vector<int> parent2 = t_other_individual->getPlainGenotype(t_depot);
  std::vector<int> child1_genotype, child2_genotype = std::vector<int>();
  child1_genotype.resize(parent1.size());
  child2_genotype.resize(parent2.size());
  int cross_point1 = rand() % parent1.size();
  int cross_point2 = rand() % parent1.size();
  int min_constr = cross_point1;
  int max_constr = cross_point2;
  if(min_constr > max_constr) {
    int temp = min_constr;
    min_constr = max_constr;
    max_constr = min_constr;
  }
  std::vector<int> values_in_section;
  std::vector<int> values_out_section;
  for(int i = 0; i < parent1.size(); i++) {
    int gen = parent1[i];
    if(i >= min_constr && i <= max_constr) {
      values_in_section.push_back(gen);
    }
    else {
      values_out_section.push_back(gen);
    }
  }
  int offset = 0;
  for(int i = 0; i < parent1.size(); i++) {
    if(i >= min_constr && i <= max_constr) {
      child1_genotype[i] = parent1[i];
    }
    else {
      int local_offset = -1;
      for(int j = 0; j < parent2.size(); j++) {
        int found = utils::findIndex(values_in_section, parent2[j]);
        if(found == -1) {
          local_offset++;
        }
        if(offset == local_offset) {
          child1_genotype[i] = parent2[j];
          offset++;
          break;
        }
      }
    }
  }
  for (int i = 0; i < parent2.size(); i++) {
    int gen = parent2[i];
    int found = utils::findIndex(values_out_section, gen);
    if(found != -1) {
      child2_genotype[i] = values_out_section[0];
      values_out_section.erase(values_out_section.begin());
    }
    else {
      child2_genotype[i] = parent2[i];
    }
  }
  return std::vector<std::vector<int>> { child1_genotype, child2_genotype };
}

std::vector<Individual*> Individual::crossover(
  Location* t_depot,
  std::vector<Location*> t_locations,
  int t_capacity,
  Individual* t_other_individual
) {
  std::vector<std::vector<int>> child_genotypes;
  switch(config::CROSSOVER_TYPE) {
    case evolution::CrossoverType::ORDERED:
      child_genotypes = orderedCrossover(t_other_individual, t_depot);
    case evolution::CrossoverType::CYCLE:
      child_genotypes = cycleCrossover(t_other_individual, t_depot);
      break;
    default:
      // error in config
      break;
  }
  Individual* child1 = new Individual(m_dimension);
  Individual* child2 = new Individual(m_dimension);
  child1->setGenotype(child_genotypes[0]);
  child1->fixGenotype(t_depot, t_locations, t_capacity);
  child2->setGenotype(child_genotypes[1]);
  child2->fixGenotype(t_depot, t_locations, t_capacity);
  return std::vector<Individual*> { child1, child2 };
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
