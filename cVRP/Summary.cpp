#include "Summary.h"
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>

Summary::Summary()
{
	m_id = -1;
}

Summary::Summary(Summary* copy)
{
	m_id = copy->m_id;
	for (int i = 0; i < copy->m_results.size(); i++) {
		m_results.push_back(copy->m_results[i]);
	}
	m_best = copy->m_best;
	m_worst = copy->m_worst;
	m_std = copy->m_std;
	m_average = copy->m_average;
}

Summary::Summary(int t_id)
{
	m_id = t_id;
}

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
	m_std = sqrt(sum / m_results.size());
	return m_std;
}


void Summary::addResult(Individual* individual)
{
	double result = individual->getFitness();
	if(result < m_best) {
		m_best = result;
		m_best_route = individual;
	}
	if(result > m_worst) {
		m_worst = result;
	}
	m_results.push_back(result);
}

void Summary::addResult(double t_result) {
	m_results.push_back(t_result);
	if(t_result < m_best) {
		m_best = t_result;
	}
	if(t_result > m_worst) {
		m_worst = t_result;
	}
}

void Summary::print() {
	std::cout << "\nBEST: " << m_best;
	std::cout << "\nWORST: " << m_worst;
	std::cout << "\nAVERAGE: " << countAverage() << " RESULTS: " << m_results.size();
	std::cout << "\nSTD: " << countStd();
}

double Summary::getBest()
{
	return m_best;
}

double Summary::getWorst()
{
	return m_worst;
}

double Summary::getAverage()
{
	return m_average;
}

double Summary::getStd()
{
	return m_std;
}

void Summary::setBest(double t_best)
{
	m_best = t_best;
}

void Summary::setWorst(double t_worst)
{
	m_worst = t_worst;
}

void Summary::setAvg(double t_avg)
{
	m_average = t_avg;
}

void Summary::setStd(double t_std)
{
	m_std = t_std;
}

Individual* Summary::getBestRoute()
{
	return m_best_route;
}
