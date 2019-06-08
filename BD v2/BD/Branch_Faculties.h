#pragma once
#include "Facult.h"

#include <map>
#include <set>

class branch_facult: public facult
	{
		std::multimap <std::string, discipline> disciplines_sorted_by_org; // Дисциплины факультета, ключ - название кафедры или организации 
	public:
// Функция сортировки дисциплин по организациям
		void sort()
			{
	/*	Так как multimap - коллекция пар ключ-значение, отсортированная по ключам,то 
		   изменяем все значения ключей на организации соответствующего контейнера      */
				for (auto i = get_disciplines().begin(); i != get_disciplines().end(); i++)
					{
						disciplines_sorted_by_org.insert(std::pair<std::string, discipline>(i->second.get_kafedra(),i->second));
					}
			}

		void UnicDiscipline()
			{
				std::set<std::string>* temp = new std::set<std::string>;
				for (auto i = get_disciplines().begin(); i != get_disciplines().end(); i++)
					{
						temp->insert(i->second.get_name());
					}
				for (auto i = disciplines_sorted_by_org.begin(); i != disciplines_sorted_by_org.end(); i++)
					{
						temp->insert(i->second.get_name());
					}
				get_unic_disciplines()=int(temp->size());
				delete temp;
			}

		void operator=(facult* temp)
			{
				get_facult_name() = temp->get_facult_name();
				get_HYK() = temp->get_HYK();
				get_count_of_kaf()=temp->get_count_of_kaf();
				get_disciplines() = temp->get_disciplines();
				UnicDiscipline();
			}

		std::multimap <std::string, discipline>* get_disciplines_sorted_by_kaf()
			{
				return &disciplines_sorted_by_org;
			}
	};