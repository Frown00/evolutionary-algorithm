#include "Experiment.h"

void Experiment::addTest(Test* test)
{
	m_tests.push_back(test);
}

std::vector<Summary*> Experiment::getOverallSummary()
{
	Test* overall = new Test(0);
	for(int j = 0; j < m_tests[0]->getSummaries().size(); j++) {
		Summary* best = new Summary();
		Summary* worst = new Summary();
		Summary* average = new Summary();
		Summary* std = new Summary();
		for(int i = 0; i < m_tests.size(); i++) {
			Summary* generation_summary = new Summary(m_tests[i]->getSummaries()[j]);
			best->addResult(generation_summary->getBest());
			worst->addResult(generation_summary->getWorst());
			average->addResult(generation_summary->getAverage());
			std->addResult(generation_summary->countStd());
		}
		double bestAvg = best->countAverage();
		double worstAvg = worst->countAverage();
		double averageAvg = average->countAverage();
		double stdAvg = std->countAverage();
		Summary* average_generation = new Summary();
		average_generation->setBest(bestAvg);
		average_generation->setWorst(worstAvg);
		average_generation->setAvg(averageAvg);
		average_generation->setStd(stdAvg);
		overall->addSummary(average_generation);
	}
	return overall->getSummaries();
}
