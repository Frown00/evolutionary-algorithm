#pragma once
#include "Loader.h"

Loader::Loader() {
  this->lines = std::vector<std::string>();
}

void Loader::readFile() {
  std::ifstream file(config::FILENAME);
  try {
    if(file.is_open()) {
      std::string line;
      while (std::getline(file, line)) {
        this->lines.push_back(line);
      }
      file.close();
    }
    std::string last_line = utils::trim(lines[lines.size() - 1]);
    if(last_line != "EOF") {
      throw ERROR_WITH_LOADING_FILE;
    }
  }
  catch(std::string e1) {
    std::cout << "ERROR: " << e1;
  }
}

VehicleRoutingProblem* Loader::getProblem() {
  VehicleRoutingProblem* vrp = new VehicleRoutingProblem();
  //const std::string name = lines.
  std::vector<std::string> name = utils::split(lines[NAME_LINE], ":");
  std::vector<std::string> comment = utils::split(lines[COMMENT_LINE], ":");
  std::vector<std::string> type = utils::split(lines[TYPE_LINE], ":");
  std::vector<std::string> dimension = utils::split(lines[DIMENSION_LINE], ":");
  std::vector<std::string> edge_weight = utils::split(lines[EDGE_WEIGHT_LINE], ":");
  std::vector<std::string> capacity = utils::split(lines[CAPACITY_LINE], ":");

  vrp->setName(utils::trim(name[1]));
  vrp->setComment(utils::trim(comment[1] + comment[2] + comment[3]));
  vrp->setType(utils::trim(type[1]));
  vrp->setDimension(stoi(utils::trim(dimension[1])));
  vrp->setEdgeWeightType(utils::trim(edge_weight[1]));
  vrp->setCapacity(stoi(utils::trim(capacity[1])));
  addLocations(vrp);
  setDemands(vrp);
  setDepot(vrp);
  return vrp;
}

void Loader::addLocations(VehicleRoutingProblem* vrp) {
  bool startLoad = false;
  for(int i = 0; i < lines.size(); i++) {
    std::string line = utils::trim(lines[i]);
    if(line == DEMAND_CONTROL_WORD) {
      break;
    }
    if(startLoad) {
      std::vector<std::string> split_line = utils::split(line, " ");
      int id = stoi(split_line[0]);
      int x = stoi(split_line[1]);
      int y = stoi(split_line[2]);
      NodeCoord* node_coord = new NodeCoord(x, y);
      Location* loc = new Location(id, node_coord);
      vrp->addLocation(loc);
    }
    if(line == NODE_CONTROL_WORD) {
      startLoad = true;
    }
    
  }
}

void Loader::setDemands(VehicleRoutingProblem* vrp) {
  bool startLoad = false;
  for(int i = 0; i < lines.size(); i++) {
    std::string line = utils::trim(lines[i]);
    if(line == DEPOT_CONTROL_WORD) {
      break;
    }
    if(startLoad) {
      std::vector<std::string> split_line = utils::split(line, " ");
      int idx = stoi(split_line[0]) - 1;
      int demand_resource = stoi(split_line[1]);
      vrp->getLocations()[idx]
         ->setDemands(demand_resource);
    }
    if(line == DEMAND_CONTROL_WORD) {
      startLoad = true;
    }
  }
}

void Loader::setDepot(VehicleRoutingProblem* vrp) {
  bool startLoad = false;
  for(int i = 0; i < lines.size(); i++) {
    std::string line = utils::trim(lines[i]);
    if(startLoad) {
      int idx = stoi(line) - 1;
      vrp->setDepot(vrp->getLocations()[idx]);
      break;
    }
    if(line == DEPOT_CONTROL_WORD) {
      startLoad = true;
    }
  }
}



