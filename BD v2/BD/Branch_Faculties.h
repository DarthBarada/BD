#pragma once
#include "Facult.h"
#include <unordered_map>
#include <algorithm>

class branch_facult: virtual public Facult
	{
		std::multimap <std::string, Facult> branch_faculties;
	public:
// Функция сортировки дисциплин по организациям
		void sort()
			{
	/*	Так как multimap - коллекция пар ключ-значение, отсортированная по ключам,то 
		   изменяем все значения ключей на организации соответствующего контейнера      */
				std::multimap <std::string, Facult>* faculties = new std::multimap <std::string, Facult>;
				Facult* temp_Facult = new Facult;
				for (auto i = branch_faculties.begin(); i != branch_faculties.end(); i++)
					{
						temp_Facult->get_facult_name() = i->second.get_facult_name();
						temp_Facult->get_HYK() = i->second.get_HYK();
						temp_Facult->get_count_of_kaf() = i->second.get_count_of_kaf();
						temp_Facult->get_unic_disciplines() = i->second.get_unic_disciplines();

						if (!i->second.get_disciplines()->empty())
							{
								for (auto j = i->second.get_disciplines()->begin(); j != i->second.get_disciplines()->end(); j++)
									{
										temp_Facult->get_disciplines()->insert(std::pair<std::string, discipline>(j->second.get_organization(), j->second));
									}
							}
						faculties->insert(std::pair <std::string, Facult>(temp_Facult->get_facult_name(), *temp_Facult));
						temp_Facult->get_disciplines()->clear();
					}
				branch_faculties.clear(); branch_faculties = *faculties;
				delete temp_Facult;
				delete faculties;
			}


		std::multimap <std::string, Facult>* get_branch_faculties()
			{
				return &branch_faculties;
			}
	};