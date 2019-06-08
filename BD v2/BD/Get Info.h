#pragma once
#include <filesystem>
#include <fstream>

#include "Manager.h"
#include "Exeption.h"
#include "Accordance.h"
/*
	Это специальный класс, чтобы получать информацию из файла, обрабатывать её и отправлять её, соответственно по факуьлтетам.
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
		std::string line;				// строка - буффер			
		facult* temp=nullptr;
		if (is_exist(destination))
			{
				std::ifstream in("Data/" + destination);
				if (in.is_open())
					{
						std::string buffer;										// строка - подбуффер
						int counter=0;											// Счетчик, чтобы программа понимала в какой контейнер ей класть информауию 
						discipline new_disc;

						while (std::getline(in, line))
							{
								if (line[0] == '1')							  //	Если в начале строки идет 1, то это базовый факультет,
									{										 //		пусть temp указывает на базовый факльтет из maneger-а,
										is_base_facult = true;
										temp = &temp_base_facult;			//		следовательно мы можем сразу работать с факультетом, используя его методы
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
								//std::cout << line << std::endl;				// Выводим полученную сторку
								for (int i = 1; i<int(line.size()); i++)		// Парсим строку
									{
										if (line[i] != '#')
											{
												buffer += line[i];
					/* Пока знак в строке не равен разделяющему - #, то добваляем по символу во 2 буффер */
											}
										else
											{
								/* Здесь как раз требуется счётчик, чтобы поочереди заполнять санчала имя, потом НУК и т.д.*/
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
																if (new_disc.get_name().empty())								// Если пустое имя, то изменяем его
																	{
																		new_disc.get_name() = buffer;
																	}
																else															// Иначе определяем количество преподавателей
																	{
																		new_disc.get_count_of_teachers() = stoi(buffer);
																		new_disc.accord();										// Находим соответствующую дисциплине кафедру и организацию
																		temp->get_disciplines().insert(std::pair <std::string, discipline>(new_disc.get_name(), new_disc));		// Добаляем дисциплину в вектор дисциплин
																		new_disc.get_name().clear();							// Чистим имя, чтобы можно не получить ошибку
																	}
															}
													}
												// Увеличивам счетчик,чтобы перейти к следующему элементу, чистим буффер
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