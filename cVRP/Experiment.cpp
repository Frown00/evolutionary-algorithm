#include "Experiment.h"

void Experiment::addTest(Test* test)
{
	m_tests.push_back(test);
}

Summary* Experiment::getOverallSummary()
{
	Summary* overall = new Summary();
	for(int i = 0; i < m_tests.size(); i++) {
		overall->addResult(m_tests[i]->getBestRoute());
	}
	overall->countAverage();
	overall->countStd();
	return overall;
}
