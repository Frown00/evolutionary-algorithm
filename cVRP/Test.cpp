#include "Test.h"

Test::Test(int id)
{
	m_id = id;
}

void Test::addSummary(Summary* t_summary)
{
	if(t_summary->getBestRoute() != nullptr) {
		if(m_best_route == nullptr) {
			m_best_route = t_summary->getBestRoute();
		}
		else {
			Individual* best_route = t_summary->getBestRoute();
			bool better = best_route->getFitness() < m_best_route->getFitness();
			if(better) {
				m_best_route = new Individual(best_route);
			}
		}
	}
	m_summaries.push_back(t_summary);
}

Individual* Test::getBestRoute()
{
	return m_best_route;
}

std::vector<Summary*> Test::getSummaries()
{
	return m_summaries;
}
