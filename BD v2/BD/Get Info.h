#pragma once
#include <filesystem>
#include <fstream>

#include "Manager.h"
#include "Exeption.h"
#include "Accordance.h"
/*
	��� ����������� �����, ����� �������� ���������� �� �����, ������������ � � ���������� �, �������������� �� �����������.
*/

class Info:public manager
	{
		bool is_base_facult=false;
		public:
		// foo for get info from file
		bool get_info(std::string destination);
	};

bool Info:: get_info(std::string destination)
	{
		std::string line;				// ������ - ������			
		facult* temp=nullptr;
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
								if (line[0] == '1')							  //	���� � ������ ������ ���� 1, �� ��� ������� ���������,
									{										 //		����� temp ��������� �� ������� �������� �� maneger-�,
										is_base_facult = true;
										temp = &temp_base_facult;			//		������������� �� ����� ����� �������� � �����������, ��������� ��� ������
									}									
								else if (line[0] == '0')
									{
										is_base_facult = false;
										temp = &temp_branch_facult;
									}
								else
									{
										std::cout << "\nERROR: File haven't specific char!";
										return false;
									}
								//std::cout << line << std::endl;				// ������� ���������� ������
								for (int i = 1; i<int(line.size()); i++)		// ������ ������
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
																temp->get_facult_name()= buffer;
																break;
															}
														case 1:
															{
																temp->get_HYK()= buffer;
																break;
															}
														case 2:
															{
																temp->get_count_of_kaf()=stoi(buffer);
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
																		temp->get_disciplines().insert(std::pair <std::string, discipline>(new_disc.get_name(), new_disc));		// �������� ���������� � ������ ���������
																		new_disc.get_name().clear();							// ������ ���, ����� ����� �� �������� ������
																	}
															}
													}
												// ���������� �������,����� ������� � ���������� ��������, ������ ������
												counter++;
												buffer.clear();
											}
									}
								if(is_base_facult==true)
									{
										temp_base_facult.UnicDiscipline();
										base_faculties.insert(std::pair<std::string, base_facult>(temp->get_facult_name(), temp_base_facult));
									}
								else
									{
										temp_branch_facult.sort();
										temp_branch_facult.UnicDiscipline();
										branch_faculties.insert(std::pair<std::string, branch_facult>(temp->get_facult_name(),temp_branch_facult));
									}
								counter = 0;
								temp->get_disciplines().clear();
							}
					}
				in.close();
			}
		return true;
	}