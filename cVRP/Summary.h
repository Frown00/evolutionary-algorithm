#pragma once
#include <vector>
#include <iostream>
#include "utils.cpp"
#include <map>
#include "Individual.h"

class Summary {
	public:
		Summary();
		Summary(Summary* copy);
		Summary(int t_id);
		double countAverage();
		double countStd();
		void addResult(Individual* individual);
		void addResult(double t_result);
		void print();
		double getBest();
		double getWorst();
		double getAverage();
		double getStd();
		void setBest(double t_best);
		void setWorst(double t_worst);
		void setAvg(double t_avg);
		void setStd(double t_std);
		Individual* getBestRoute();
	private:
		int m_id;
		std::vector<double> m_results;
		Individual* m_best_route;
		double m_best = INFINITY;
		double m_worst = -1;
		double m_average;
		double m_std;
};

