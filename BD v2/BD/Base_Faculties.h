#pragma once
#include "Facult.h"

#include <set>

class base_facult: public facult
	{
	public:

		void UnicDiscipline()
			{
				std::set<std::string>* temp = new std::set<std::string>;
				for (auto i = get_disciplines().begin(); i != get_disciplines().end(); i++)
					{	
						temp->insert(i->second.get_name());
					}
				get_unic_disciplines() = int(temp->size());
				delete temp;
			}

		void operator=(facult* temp)
		{
			get_facult_name() = temp->get_facult_name();
			get_HYK() = temp->get_HYK();
			get_count_of_kaf() = temp->get_count_of_kaf();
			get_disciplines() = temp->get_disciplines();
			UnicDiscipline();
		}
	};