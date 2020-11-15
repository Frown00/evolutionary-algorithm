#pragma once
#include "Summary.h"

class Test
{
	public:
		Test(int id);
		void addSummary(Summary* t_summary);
		Individual* getBestRoute();
		std::vector<Summary*> getSummaries();
	private:
		int m_id;
		Individual* m_best_route = nullptr;
		std::vector<Summary*> m_summaries;

};

