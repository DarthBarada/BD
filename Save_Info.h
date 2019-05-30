#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "Branch_Faculties.h"
#include "Base_Faculties.h"

#include "Exeption.h"

class save: virtual public branch_facult, virtual public base_facult
{
public:
	// Функция сохраняет всю информацию о базовых и отраслевых факультетах 
	void saver()
		{
			std::ofstream out;
			if (!std::experimental::filesystem::exists("Data"))
				{
					std::cout << "\nFolder \"Data\" created!\n";
					std::experimental::filesystem::create_directory("Data");
				}
			out.open("Data/Faculties.txt");
			/* Так как в unordered_multimap нельзя обращаться к элементу, то для меня легким способым было перевести его в vector, 
			   так как последовательность будет сохраняться */

			for (int i = 0; i<int(base_faculties.size()); i++)
				{
					out << base_faculties.at(i).get_facult_name() << '#' << base_faculties.at(i).get_HYK() << '#' << base_faculties.at(i).get_count_of_kaf() << '#';
					for (int kol = 0; kol<int(base_faculties.at(i).get_disciplines()->size()); kol++)
						{
							out << base_faculties.at(i).get_disciplines()->at(i).get_name() << '#' << base_faculties.at(i).get_disciplines()->at(i).get_count_of_teachers() << '#';
						}
					out << std::endl;
				} 
			for (int i = 0; i<int(branch_faculties.size()); i++)
				{
					out << branch_faculties.at(i).get_facult_name() << '#' << branch_faculties.at(i).get_HYK() << '#' << branch_faculties.at(i).get_count_of_kaf() << '#';
					for (int kol = 0; kol<int(branch_faculties.at(i).get_disciplines()->size()); kol++)
						{
							out << branch_faculties.at(i).get_disciplines()->at(i).get_name() << '#' << branch_faculties.at(i).get_disciplines()->at(i).get_count_of_teachers() << '#';
						}
					out << std::endl;
				}
			out.close();
		}
/* Функция сохраняет вектор с названием в файл*/
	void save_other(std::vector <facult> temp, std::string destination)
		{
			std::ofstream out;
			if (!std::experimental::filesystem::exists("Data"))
				{
					std::cout << "\nFolder \"Data\" created!\n";
					std::experimental::filesystem::create_directory("Data");
				}
			out.open(destination);
			for (int i = 0; i<int(temp.size()); i++)
				{
					out << temp.at(i).get_facult_name() << '#' << temp.at(i).get_HYK() << '#' << temp.at(i).get_count_of_kaf() << '#';
					for (int kol = 0; kol<int(temp.at(i).get_disciplines()->size()); kol++)
						{
							out << temp.at(i).get_disciplines()->at(kol).get_name() << '#' << temp.at(i).get_disciplines()->at(kol).get_count_of_teachers() << '#';
						}
					out << std::endl;
				}

			temp.clear();
			out.close();
		}
	/* Функция сохраняет факультет с названием в файл*/
	void save_facult(facult* temp, std::string destination) const
		{
			std::ofstream out;
			if (!std::experimental::filesystem::exists("Data"))
				{
					std::cout << "\nFolder \"Data\" created!\n";
					std::experimental::filesystem::create_directory("Data");
				}
			if (is_txt(destination))
				{
					out.open(destination);
					out << temp->get_facult_name() << '#' << temp->get_HYK() << '#' << temp->get_count_of_kaf() << '#';
					for (int i = 0; i<int(temp->get_disciplines()->size()); i++)
						{
							out << temp->get_disciplines()->at(i).get_name() << '#' << temp->get_disciplines()->at(i).get_count_of_teachers() << '#';
						}
				}
			out.close();
		}
};