#pragma once
#include "Facult.h"
#include <map>
#include <algorithm>

class base_facult: virtual public Facult
	{
		std::multimap <std::string, Facult> base_faculties;
	public:
// Функция сортировки дисциплин по кафедрам
		void sort()
			{
	/*	Так как multimap - коллекция пар ключ-значение, отсортированная по ключам,то
			изменяем все значения ключей на кафедры соответствующего контейнера         */
			std::multimap <std::string, Facult>* faculties = new std::multimap <std::string, Facult>;
			Facult* temp_Facult = new Facult;
				for (auto i = base_faculties.begin(); i != base_faculties.end(); i++)
					{
						temp_Facult->get_facult_name() = i->second.get_facult_name();
						temp_Facult->get_HYK() = i->second.get_HYK();
						temp_Facult->get_count_of_kaf() = i->second.get_count_of_kaf();
						temp_Facult->get_unic_disciplines() = i->second.get_unic_disciplines();

						if (!i->second.get_disciplines()->empty())
							{
								for (auto j = i->second.get_disciplines()->begin(); j != i->second.get_disciplines()->end(); j++)
									{
										temp_Facult->get_disciplines()->insert(std::pair<std::string, discipline>(j->second.get_kafedra(),j->second));
									}
							}
						faculties->insert(std::pair <std::string, Facult>(temp_Facult->get_facult_name(), *temp_Facult));
						temp_Facult->get_disciplines()->clear();
					}
				base_faculties.clear(); base_faculties = *faculties;
				delete temp_Facult;
				delete faculties;
			}
	
		std::multimap <std::string, Facult>* get_base_faculties()
			{
				return &base_faculties;
			}
	};