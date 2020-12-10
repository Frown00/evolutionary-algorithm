#include "Configuration.h"

Configuration::Configuration()
{

}

void Configuration::setProblem(std::string t_problem)
{
	m_instance_problem = t_problem;
	m_file_path = "./problems/" + m_instance_problem + ".vrp";
}

std::string Configuration::getInstanceProblem()
{
	return m_instance_problem;
}

std::string Configuration::getFilePath()
{
	return m_file_path;
}
