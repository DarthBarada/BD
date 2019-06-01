#pragma once
#include "Facult.h"
#include <unordered_map>
#include <algorithm>

class base_facult: virtual public facult
	{
	public:
// Функция сортировки дисциплин по кафедрам
		void sort()
			{
	/*	Так как multimap - коллекция пар ключ-значение, отсортированная по ключам,то
			изменяем все значения ключей на кафедры соответствующего контейнера         */
				if (!get_disciplines()->empty())
					{
						std::for_each(get_disciplines()->begin(), get_disciplines()->end(), [](std::pair <std::string, discipline> temp)
							{
								temp.first = temp.second.get_kafedra();
							});
					}
				else
					{
						std::cout << "Nothing to sort!\n";
					}
			}
	};