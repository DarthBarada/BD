#pragma once
#include "Facult.h"


#include <map>
#include <iostream>
#include <algorithm>
#include <iomanip>


struct print
	{
		void print_discs(std::multimap <std::string, Facult> temp) const
			{
			
				int pos = 0;
			
				std::cout << std::left << "\n" << std::setw(4) << "¹" << std::setw(40) << "Discipline" << std::setw(20) << "Department" << std::setw(20) << "Organization" << std::setw(21) << "Number of teachers" << "\n";
			
				for (auto i = temp.begin(); i!= temp.end(); i++)
					{
						for (auto j = i->second.get_disciplines()->begin(); j!=i->second.get_disciplines()->end(); j++)
							{	
								std::cout << std::left << std::setw(4) << pos + 1 << std::setw(40) << j->second.get_name() << std::setw(20) << j->second.get_kafedra() << std::setw(20)
									<< j->second.get_organization() << std::setw(21) << j->second.get_count_of_teachers();
								std::cout << std::endl;
								pos++;
							}
					}
			}

		void print_discs(Facult temp) const
			{
				int pos = 0;

				std::cout << std::left << "\n"<<std::setw(4)<<"¹"<<std::setw(40)<<"Discipline" << std::setw(20) <<"Department" << std::setw(20) <<"Organization" << std::setw(21) <<"Number of teachers"<<"\n";
				
				for (auto j = temp.get_disciplines()->begin(); j!= temp.get_disciplines()->end(); j++)
					{
						std::cout << std::left << std::setw(4) << pos + 1 << std::setw(40) << j->second.get_name() << std::setw(20) << j->second.get_kafedra() << std::setw(20)
							<< j->second.get_organization() << std::setw(21) << j->second.get_count_of_teachers();
						std::cout << std::endl;
						pos++;
					}
			}

		void print_facults(std::multimap <std::string, Facult> temp) const
			{
				if (!temp.empty())
					{
						for (auto i = temp.begin(); i!= temp.end(); i++)
							{
								std::cout << std::left << "\n" << std::setw(10) << "Faculty" << std::setw(50) << "HYK" << std::setw(24) << "Number of departments" << std::setw(19) << "Unic disciplines" << "\n";
								std::cout << std::left << std::setw(10)<< i->second.get_facult_name() << std::setw(50)<< i->second.get_HYK() << std::setw(24) << i->second.get_count_of_kaf() << std::setw(19) << i->second.get_unic_disciplines();
								std::cout << std::endl;
								print_discs(i->second);
								std::cout << std::endl;
							}
					}
			}

		void print_facult(Facult temp) const
			{
				std::cout << std::left << "\n" << std::setw(10) << "Faculty" << std::setw(50) << "HYK" << std::setw(24) << "Number of departments" << std::setw(19) << "Unic disciplines" << "\n";
				std::cout << std::left << std::setw(10) << temp.get_facult_name() << std::setw(50) << temp.get_HYK() << std::setw(24) << temp.get_count_of_kaf() << std::setw(19)<< temp.get_unic_disciplines();
				std::cout << std::endl;
				print_discs(temp);
			}

		void print_just_facult(Facult temp) const
			{
				std::cout << std::left << std::setw(10) << temp.get_facult_name() << std::setw(50) << temp.get_HYK() << std::setw(24) << temp.get_count_of_kaf() << std::endl;
			}
		void print_just_facult(std::multimap <std::string, Facult> temp) const
			{	
				for (auto i = temp.begin(); i!= temp.end(); i++)
					{
						std::cout << std::left << std::setw(10) << i->second.get_facult_name() << std::setw(50) << i->second.get_HYK() << std::setw(24) << i->second.get_count_of_kaf() << std::setw(19) << i->second.get_unic_disciplines() << std::endl;
					}
			}
		void print_all (std::multimap <std::string, Facult> temp1, std::multimap <std::string, Facult> temp2) const
			{
				print_facults(temp1);
				print_facults(temp2);
			}
	};