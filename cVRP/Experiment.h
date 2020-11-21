#pragma once
#include "Test.h"

class Experiment
{
	public:
		void addTest(Test* test);
		Summary* getOverallSummary();
	private:
		std::vector<Test*> m_tests;
		
};

