#pragma once
#include "Configuration.h"

class EvolutionConfig : public Configuration
{
	public:
		EvolutionConfig();
		void setPopulationSize(int t_pop_size);
		void setGenerations(int t_gen);
		void setPX(double t_px);
		void setPM(int t_pm);
		void setTournamentPercent(int t_tour);
		void setMutationType(MutationType m_type);
		void setCrossoverType(CrossoverType m_type);
		void setSelectionType(SelectionType m_type);

		double getPX();
		double getPM();
		double getTour();
		int getPopSize();
		int getGenerations();

		MutationType getMutationType();
		CrossoverType getCrossoverType();
		SelectionType getSelectionType();

	private:
		int m_population_size;
		int m_generations;
		double m_px;
		double m_pm;
		double m_tour;
		MutationType m_mutation_type;
		CrossoverType m_crossover_type;
		SelectionType m_selection_type;
};
