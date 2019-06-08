#pragma once
// KOHCTPYKTOP

/* Позволяет создавать элементв БД */
#include <iostream>
#include <Windows.h>

#include "Exeption.h"
#include "Save_Info.h"
#include "Manager.h"

#include <conio.h>

class KOHCTPYKTOP:public manager, public save
	{
		public:
			// Создаёт один факультет 
			void create_facult();
			// Создаёт дисциплину
			discipline create_discipline();
			// Создаёт БД
			void create_faculties(int kol);
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
		facult* temp=nullptr;
		std::string buffer;
		bool is_base_facult=false;
		int kol;

		std::cout << "\nEnter name of facult: ";
		do
			{
				std::cin >> buffer;
				if (similar_facult(buffer) == 0)
					{
						std::cout << "Unknown facult!\n";
						std::cout << "List of available facults: ";
						std::for_each(base_facults_name.begin(), base_facults_name.end(), [](std::string temp) 
							{	
								std::cout << temp + ", ";
							});
						std::for_each(branch_facults_name.begin(), branch_facults_name.end(), [](std::string temp)
							{
								std::cout << temp + ", ";
							});
					}
			} while (similar_facult(buffer) == 0);

		if (similar_facult(buffer) == 1)
			{
				is_base_facult = true;
				temp = &temp_base_facult;
			}
		else
			{
				temp = &temp_branch_facult;
			}
		temp->get_facult_name() = buffer;

		std::cout << "\nEnter HYK: ";
		std::cin >> buffer;
		temp->get_HYK() = buffer;

		std::cout << "\nEnter count of kaf: ";
		cin(temp->get_count_of_kaf());
		temp->UnicDiscipline();

		std::cout << "\nEnter count of disciplines that you enter: ";
		cin(kol);

		for (int i = 0; i < kol; i++)
			{
				temp->get_disciplines().insert(std::pair<std::string,discipline>(create_discipline().get_name(),create_discipline()));
			}

		bufferzone.insert(std::pair<std::string, facult*>(temp->get_facult_name(), temp));

		if (is_base_facult == true)
			{
				created_base_faculties.insert(std::pair<std::string, base_facult>(temp_base_facult.get_facult_name(), temp_base_facult));
			}
		else
			{
				created_branch_faculties.insert(std::pair<std::string, branch_facult>(temp_branch_facult.get_facult_name(), temp_branch_facult));
			}
		delete temp;
	}	

void KOHCTPYKTOP::create_faculties(int kol)
	{
		bufferzone.clear();
		for (int i = 0; i < kol; i++)
			{
				create_facult();
			}
		transform();
	}