#include "Summary.h"

double Summary::countAverage() {
	double sum = 0;
	for(int i = 0; i < m_results.size(); i++) {
		sum += m_results[i];
	}
	m_average = sum / m_results.size();
	return m_average;
}

double Summary::countStd() {
	double avg = countAverage();
	double sum = 0;
	for(int i = 0; i < m_results.size(); i++) {
		sum += pow((m_results[i] - avg), 2);
	}
	m_std = sqrt(sum / avg);
	return m_std;
}

void Summary::addResult(int t_id, double t_result) {
	m_results.push_back(t_result);
	if(t_result < m_best) {
		m_best = t_result;
		m_best_id = t_id;
	}
	if(t_result > m_worst) {
		m_worst = t_result;
		m_worst_id = t_id;
	}
}

void Summary::print() {
	std::cout << "\nBEST: " << m_best << " ID: " << m_best_id;
	std::cout << "\nWORST: " << m_worst << " ID: " << m_worst_id;
	std::cout << "\nAVERAGE: " << countAverage() << " RESULTS: " << m_results.size();
	std::cout << "\nSTD: " << countStd();
}
