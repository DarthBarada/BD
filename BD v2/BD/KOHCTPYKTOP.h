#pragma once
// KOHCTPYKTOP
#include <iostream>
#include <Windows.h>
//#include 

#include "Exeption.h"
#include "Save_Info.h"

#include "Accordance.h"

class KOHCTPYKTOP:virtual public discipline, virtual public save
	{
	public:
		void create_facult();
		discipline create_discipline();
		std::multimap <std::string, Facult> create_faculties(int kol);
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
		Facult* temp = new Facult;
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
				temp->get_disciplines()->insert(std::pair<std::string,discipline>(create_discipline().get_name(),create_discipline()));
			}
		if (similar_facult(temp->get_facult_name()) == 1)
			{
				get_base_faculties()->insert(std::pair<std::string, Facult>(temp->get_facult_name(), *temp));
			}
		else if (similar_facult(temp->get_facult_name()) == 2)
			{
				get_branch_faculties()->insert(std::pair<std::string, Facult>(temp->get_facult_name(), *temp));
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

std::multimap <std::string, Facult> KOHCTPYKTOP::create_faculties(int kol)
	{
		std::multimap<std::string, Facult>* temp_map = new std::multimap<std::string, Facult>;
		Facult *temp = new Facult;
		for (int i = 0; i < kol; i++)
			{
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
						temp->get_disciplines()->insert(std::pair<std::string, discipline>(create_discipline().get_name(), create_discipline()));
					}
			}
		return *temp_map;
		delete temp;delete temp_map;
	}