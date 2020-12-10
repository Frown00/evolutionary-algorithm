#pragma once
#include "Enums.h"
#include "ProblemNames.h"

class Configuration
{
	public:
		Configuration();
		void setProblem(std::string t_problem);
		std::string getInstanceProblem();
		std::string getFilePath();

	protected:
		std::string m_instance_problem;
	
	private:
		std::string m_file_path = "./problems/";
};

