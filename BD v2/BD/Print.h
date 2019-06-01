#pragma once
#include "Facult.h"


#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>


struct print
	{
		void print_discs(std::vector <facult> temp) const
			{
			std::cout << std::left << "\n" << std::setw(4) << "¹" << std::setw(40) << "Discipline" << std::setw(20) << "Department" << std::setw(20) << "Organization" << std::setw(21) << "Number of teachers" << "\n";
				for (int i = 0; i<int(temp.size()); i++)
					{
						for (int j = 0; j<int(temp.at(i).get_disciplines()->size()); j++)
							{
								std::cout << std::left << std::setw(4) << j + 1 << std::setw(40) << temp.at(i).get_disciplines()->at(j).get_name() << std::setw(20) << temp.at(i).get_disciplines()->at(j).get_kafedra() << std::setw(20)
										  << temp.at(i).get_disciplines()->at(j).get_organization() << std::setw(21) << temp.at(i).get_disciplines()->at(j).get_count_of_teachers();
								std::cout << std::endl;
							}
					}
			}

		void print_discs(facult temp) const
			{
				std::cout << std::left << "\n"<<std::setw(4)<<"¹"<<std::setw(40)<<"Discipline" << std::setw(20) <<"Department" << std::setw(20) <<"Organization" << std::setw(21) <<"Number of teachers"<<"\n";
				for (int j = 0; j<int(temp.get_disciplines()->size()); j++)
					{
						std::cout << std::left <<std::setw(4) <<j+1<<std::setw(40) << temp.get_disciplines()->at(j).get_name() << std::setw(20) << temp.get_disciplines()->at(j).get_kafedra() << std::setw(20)
							<< temp.get_disciplines()->at(j).get_organization() << std::setw(21) << temp.get_disciplines()->at(j).get_count_of_teachers();
						std::cout << std::endl;
					}
			}

		void print_facults(std::vector <facult> temp) const
			{
				if (!temp.empty())
					{
						for (int i = 0; i<int(temp.size()); i++)
							{
								std::cout << std::left << "\n" << std::setw(10) << "Faculty" << std::setw(50) << "HYK" << std::setw(24) << "Number of departments" << std::setw(19) << "Unic disciplines" << "\n";
								std::cout << std::left << std::setw(10)<< temp.at(i).get_facult_name() << std::setw(50)<< temp.at(i).get_HYK() << std::setw(24) << temp.at(i).get_count_of_kaf() << std::setw(19) << temp.at(i).get_unic_disciplines();
								std::cout << std::endl;
								print_discs(temp.at(i));
								std::cout << std::endl;
							}
					}
			}

		void print_facult(facult temp) const
			{
				std::cout << std::left << "\n" << std::setw(10) << "Faculty" << std::setw(50) << "HYK" << std::setw(24) << "Number of departments" << std::setw(19) << "Unic disciplines" << "\n";
				std::cout << std::left << std::setw(10) << temp.get_facult_name() << std::setw(50) << temp.get_HYK() << std::setw(24) << temp.get_count_of_kaf() << std::setw(19)<< temp.get_unic_disciplines();
				std::cout << std::endl;
				print_discs(temp);
			}

		void print_just_facult(facult temp) const
			{
				std::cout << std::left << std::setw(10) << temp.get_facult_name() << std::setw(50) << temp.get_HYK() << std::setw(24) << temp.get_count_of_kaf() << std::endl;
			}
		void print_just_facult(std::vector <facult> temp) const
			{	
				for (int i = 0; i<int(temp.size()); i++)
					{
						std::cout << std::left << std::setw(10) << temp.at(i).get_facult_name() << std::setw(50) << temp.at(i).get_HYK() << std::setw(24) << temp.at(i).get_count_of_kaf() << std::setw(19) << temp.at(i).get_unic_disciplines() << std::endl;
					}
			}

		void print_all (std::vector <facult> temp1, std::vector <facult> temp2) const
			{
				print_facults(temp1);
				print_facults(temp2);
			}
	};