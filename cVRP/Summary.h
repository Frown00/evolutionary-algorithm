#pragma once
#include <vector>
#include <iostream>

class Summary {
	public:
		double countAverage();
		double countStd();
		void addResult(int id, double t_result);
		void print();
	private:
		std::vector<double> m_results;
		double m_best = INFINITY;
		int m_best_id;
		double m_worst = -1;
		int m_worst_id;
		double m_average;
		double m_std;
};

