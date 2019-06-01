#pragma once
#include <string>
#include <iostream>

#include "Accordance.h"

class discipline // ������: ��������, �������, ���������� ��������
	{
			std::string name; // �������� ����������
			std::string kafedra; // �������� �������
			std::string organization; // �������� �����������
			int count_of_teachers; // ���������� ��������
		public:
// ������� ��������� ���������� �� �������� ���������� ������� � �����������
			void accord()										
				{
					kafedra = similar_disc_kaf(name);
					organization = similar_kaf_organization(kafedra);
				}

			discipline() :name(name), kafedra(kafedra), organization(organization), count_of_teachers(count_of_teachers)
				{	}
			discipline(std::string nazvanie, std::string department, std::string company, int teachers)
				{
					name = nazvanie; kafedra = department; organization = company; count_of_teachers = teachers;
				}
			~discipline()
				{	
					name.clear();
					kafedra.clear();
					organization.clear();
					count_of_teachers = 0;
				}
	///----------------------------------

			 std::string& get_name()  
				{
					return name;
				}

			 std::string& get_kafedra()  
				{
					return kafedra;
				}

			 std::string& get_organization()
				{
						return organization;
				}

			int& get_count_of_teachers()
				{
					return count_of_teachers;
				}
	};