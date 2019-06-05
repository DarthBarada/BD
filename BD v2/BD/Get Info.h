#pragma once
#include <filesystem>
#include <fstream>

#include "Branch_Faculties.h"
#include "Base_Faculties.h"
#include "Exeption.h"
#include "Accordance.h"
/*
	��� ����������� �����, ����� �������� ���������� �� �����, ������������ � � ���������� �, �������������� �� �����������.
*/
class Info:virtual public base_facult, virtual public branch_facult
	{
	// ���������� �������������� ���������� ��-�� ����������
		void sort() = 0;
		// foo for sort faculties 
		public:
		// foo for get info from file
		void get_info(std::string destination);
	};

void Info:: get_info(std::string destination)
	{
		std::string line;								// ������ - ������
		Facult *temp = new Facult;			

		if (is_exist(destination))
			{
				std::ifstream in("Data/" + destination);
				if (in.is_open())
					{
						std::string buffer;										// ������ - ���������
						int counter=0;											// �������, ����� ��������� �������� � ����� ��������� �� ������ ���������� 
						discipline new_disc;

						while (std::getline(in, line))
							{
								//std::cout << line << std::endl;				// ������� ���������� ������
								
								for (int i = 0; i<int(line.size()); i++)		// ������ ������
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
																temp->get_facult_name() = buffer;
																break;
															}
														case 1:
															{
																temp->get_HYK() = buffer;
																break;
															}
														case 2:
															{
																temp->get_count_of_kaf() = stoi(buffer);
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
																		new_disc.get_count_of_teachers() = stoi(buffer);
																		new_disc.accord();										// ������� ��������������� ���������� ������� � �����������
																		temp->get_disciplines()->insert(std::pair <std::string, discipline>(new_disc.get_name(), new_disc));		// �������� ���������� � ������ ���������
																		new_disc.get_name().clear();							// ������ ���, ����� ����� �� �������� ������
																	}
															}
													}
												// ���������� �������,����� ������� � ���������� ��������, ������ ������
												counter++;
												buffer.clear();
											}
									}
								temp->UnicDiscipline();
								temp->get_unic_disciplines();
								
								if (similar_facult(temp->get_facult_name())==1)
									{
										get_base_faculties()->insert(std::pair<std::string, Facult>(temp->get_facult_name(),*temp));
									}
								else if(similar_facult(temp->get_facult_name()) == 2)
									{
										get_branch_faculties()->insert(std::pair<std::string, Facult>(temp->get_facult_name(), *temp));
									}
								counter = 0;
								temp->get_disciplines()->clear();
							}
					}
				in.close();
			}
		base_facult::sort();			// ��������� ����������
		branch_facult::sort();
		delete temp;						// ������ ������
	}