#pragma once
// KOHCTPYKTOP
#include <iostream>
#include <Windows.h>
//#include 

#include "Base_Faculties.h"
#include "Branch_Faculties.h"

#include "Facult.h"
#include "Discipline.h"

#include "Exeption.h"
#include "Save_Info.h"

class KOHCTPYKTOP:virtual public discipline, virtual public save
	{
	public:
		void create_facult();
		discipline create_discipline();
		std::vector <facult> create_faculties(int kol);
	};

discipline KOHCTPYKTOP::create_discipline()
	{
		discipline* temp = new discipline;
		std::string buffer;

		std::cout << "\nEnter name of discipline: ";
		do
			{
				std::cin >> buffer;
			} while (buffer.empty());
		temp->get_name() = buffer;		    buffer.clear();

		std::cout << "\nEnter count of teachers: ";
		cin(temp->get_count_of_teachers());

		temp->accord();
		return *temp;

		delete temp;
	}

void KOHCTPYKTOP::create_facult()
	{
		facult* temp = new facult;
		std::string buffer;
		int kol;

		std::cout << "\nEnter name of facult: ";
		std::cin >> buffer;
		temp->get_facult_name() = buffer;			buffer.clear();

		std::cout << "\nEnter HYK: ";
		std::cin >> buffer;
		temp->get_HYK() = buffer;	buffer.clear();

		std::cout << "\nEnter count of kaf: ";
		cin(temp->get_count_of_kaf());

		std::cout << "\nEnter count of disciplines that you enter: ";
		cin(kol);

		for (int i = 0; i < kol; i++)
			{
				temp->get_disciplines()->push_back(create_discipline());
			}

		if (temp->get_facult_name() == "РКТ" || temp->get_facult_name() == "АК" || temp->get_facult_name() == "ПС" || temp->get_facult_name() == "РТ" || temp->get_facult_name() == "ОЭП")
			{
				branch_faculties.push_back(*temp); // Отраслевые факультеты
			}
		else
			{
				base_faculties.push_back(*temp); // Базовые факультеты
			}

		std::cout << "Want to save this facult (1 - yes; 0 - no)? ";
		do
			{
				cin(kol);
			} while (kol != 0 && kol != 1);
		if (kol = 1)
			{
				save_facult(temp,"Data/facult.txt");
			}
		kol = 0;
		delete temp;
	}	

std::vector <facult> KOHCTPYKTOP::create_faculties(int kol)
	{
		std::vector<facult>* temp = new std::vector<facult>;
		temp->resize(kol);
		for (int i = 0; i < kol; i++)
			{
				std::string buffer;
				int kol;

				std::cout << "\nEnter name of facult: ";
				std::cin >> buffer;
				temp->at(i).get_facult_name() = buffer;			buffer.clear();

				std::cout << "\nEnter HYK: ";
				std::cin >> buffer;
				temp->at(i).get_HYK() = buffer;	buffer.clear();

				std::cout << "\nEnter count of kaf: ";
				cin(temp->at(i).get_count_of_kaf());

				std::cout << "\nEnter count of disciplines that you enter: ";
				cin(kol);

				for (int i = 0; i < kol; i++)
					{
						temp->at(i).get_disciplines()->push_back(create_discipline());
					}
			}
		return *temp;
		delete temp;
	}