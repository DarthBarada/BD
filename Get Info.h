#pragma once
#include <filesystem>
#include <fstream>

#include "Branch_Faculties.h"
#include "Base_Faculties.h"
#include "Exeption.h"
/*
	��� ����������� �����, ����� �������� ���������� �� �����, ������������ � � ���������� �, �������������� �� �����������.
*/
class Info:virtual public base_facult, virtual public branch_facult
	{
		std::vector <facult> faculties; // <- buffer
		// foo for sort faculties 
		void sort();
		public:
		// foo for get info from file
		void get_info(std::string destination);
	};

void Info::sort()
	{
		for (int i = 0; i<int(faculties.size()); i++)
			{
				faculties.at(i).UnicDiscipline();
				if (faculties.at(i).get_facult_name() == "���" || faculties.at(i).get_facult_name() == "��" || faculties.at(i).get_facult_name() == "��" || faculties.at(i).get_facult_name() == "��" || faculties.at(i).get_facult_name() == "���")
					{
						faculties.at(i).sortbyorg();
						branch_faculties.push_back(faculties.at(i)); // ���������� ����������
					}
				else
					{
						faculties.at(i).sortbykaf(); // ��������� ���������� �� ��������
						base_faculties.push_back(faculties.at(i)); // ������� ����������
					}
			}
	}

void Info:: get_info(std::string destination)
	{
		std::string line; // ������ - ������
		if (is_exist(destination))
			{
				std::ifstream in("Data/" + destination);
				if (in.is_open())
					{
						std::string buffer;
						int counter=0; // �������, ����� ��������� �������� � ����� ��������� �� ������ ���������� 
						facult new_facult;
						discipline new_disc;

						while (std::getline(in, line))
							{
								//std::cout << line << std::endl; // ������� ���������� ������
								
								for (int i = 0; i<int(line.size()); i++) // ������ ������
									{
										if (line[i] != '#')
											{
												buffer += line[i];
					/* ���� ���� � ������ �� ����� ������������ - #, �� ��������� �� ������� �� 2 ������ */
											}
										else
											{
								/* ����� ��� ��� ��������� �������, ����� ��������� ��������� ������� ���, ����� ��� � �.�.*/
												switch (counter)
													{
														case 0:
															{
															new_facult.get_facult_name()=buffer;
															break;
															}
														case 1:
															{
																new_facult.get_HYK()=buffer;
																break;
															}
														case 2:
															{
																new_facult.get_count_of_kaf()=stoi(buffer);
																break;
															}
														default:
															{
																if (new_disc.get_name().empty())								// ���� ������ ���, �� �������� ���
																	{
																		new_disc.get_name() = buffer;
																	}
																else															// ����� ���������� ���������� ��������������
																	{
																		new_disc.get_count_of_teachers()=stoi(buffer);
																		new_disc.accord();										// ������� ��������������� ���������� ������� � �����������
																		new_facult.get_disciplines()->push_back(new_disc);		// �������� ���������� � ������ ���������
																		new_disc.get_name().clear();							// ������ ���, ����� ����� �� �������� ������
																	}
															}
													}
												// ���������� �������,����� ������� � ���������� ��������, ������ ������
												counter++;
												buffer.clear();
											}
									}
								new_facult.get_unic_disciplines();
								faculties.push_back(new_facult);
								new_facult.get_disciplines()->clear();
								counter = 0;
							}
						sort();

						if (!faculties.empty())
							{
								faculties.clear(); /* ������� ������, ����� �� ������� ��� �������� ��������� */
							}
					}
				in.close();
			}
	}