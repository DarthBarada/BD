#pragma once
#include "Discipline.h"

#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

class facult
	{
		std::string name; // Название факультета
		std::string HYK; // Название НУК
		int count_of_kaf; // количество кафедр
		std::vector <discipline> disciplines; // Дисциплины факультета, ключ - название кафедры или организации 
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

		// Функция для нахлождения соответствующей кафедры и организации
		void accord()
			{
				if (!disciplines.empty())
					{
						std::for_each(disciplines.begin(), disciplines.end(),accord);
					}
			}

		void UnicDiscipline()
			{
				std::set<std::string> temp;
				for (int i = 0; i<int(disciplines.size()); i++)
					{
						temp.insert(disciplines.at(i).get_name());
					}
				unic_disciplines=temp.size();

				temp.clear();
			}

		void sortbyorg()
			{
				for (int i = 0; i < int(disciplines.size()); i++)
					{
						for (int j = i + 1; j<int(disciplines.size()); j++)
							{
								if (disciplines.at(i).get_organization() < disciplines.at(j).get_organization())
									{
										std::swap(disciplines.at(i), disciplines.at(j));
									}
							}
					}
			}

		void sortbykaf()
			{
				for (int i = 0; i<int(disciplines.size()); i++)
					{
						for (int j = i+1; j<int(disciplines.size()); j++)
							{
								if (disciplines.at(i).get_kafedra() < disciplines.at(j).get_kafedra())
									{
										std::swap(disciplines.at(i), disciplines.at(j));
									}
							}
					}
			}


///-------------------------------------------

		int& get_count_of_kaf()
			{
				return count_of_kaf;
			}

		int get_unic_disciplines() 
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

		std::vector <discipline>* get_disciplines()
			{
				return &disciplines;
			}
	};