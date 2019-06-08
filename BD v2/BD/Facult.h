#pragma once
#include "Discipline.h"

#include <string>
#include <map>
#include <algorithm>
#include <string>

class facult
	{
		std::string name;									   // Название факультета
		std::string HYK;									  // Название НУК
		int count_of_kaf;									 // количество кафедр
		std::multimap <std::string,discipline> disciplines; // Дисциплины факультета, ключ - название кафедры
		int unic_disciplines;

		public:

			facult()
				{
					unic_disciplines = 0;
					count_of_kaf = 0;
					disciplines.clear();
				}
			~facult()
				{
					name.clear();
					HYK.clear();
					count_of_kaf = 0;
					unic_disciplines = 0;
					disciplines.clear();
				}
			
			virtual void UnicDiscipline() = 0;

///-------------------------------------------

			int& get_count_of_kaf()
				{
					return count_of_kaf;
				}
			int& get_unic_disciplines()
				{
					return unic_disciplines;
				}
			std::string& get_facult_name()
				{
					return name;
				}
			std::string& get_HYK()
				{
					return HYK;
				}
			std::multimap <std::string, discipline>& get_disciplines()
				{
					return disciplines;
				}
	};