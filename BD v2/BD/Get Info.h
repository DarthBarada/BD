#pragma once
#include <filesystem>
#include <fstream>

#include "Branch_Faculties.h"
#include "Base_Faculties.h"
#include "Exeption.h"
#include "Accordance.h"
/*
	Это специальный класс, чтобы получать информацию из файла, обрабатывать её и отправлять её, соответственно по факуьлтетам.
*/
class Info:virtual public base_facult, virtual public branch_facult
	{
	// Приходится переопределять сортировку из-за конфликтов
		void sort() = 0;
		// foo for sort faculties 
		public:
		// foo for get info from file
		void get_info(std::string destination);
	};

void Info:: get_info(std::string destination)
	{
		std::string line;								// строка - буффер
		Facult *temp = new Facult;			

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
								//std::cout << line << std::endl;				// Выводим полученную сторку
								
								for (int i = 0; i<int(line.size()); i++)		// Парсим строку
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
																if (new_disc.get_name().empty())								// Если пустое имя, то изменяем его
																	{
																		new_disc.get_name() = buffer;
																	}
																else															// Иначе определяем количество преподавателей
																	{
																		new_disc.get_count_of_teachers() = stoi(buffer);
																		new_disc.accord();										// Находим соответствующую дисциплине кафедру и организацию
																		temp->get_disciplines()->insert(std::pair <std::string, discipline>(new_disc.get_name(), new_disc));		// Добаляем дисциплину в вектор дисциплин
																		new_disc.get_name().clear();							// Чистим имя, чтобы можно не получить ошибку
																	}
															}
													}
												// Увеличивам счетчик,чтобы перейти к следующему элементу, чистим буффер
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
		base_facult::sort();			// Сортируем факультеты
		branch_facult::sort();
		delete temp;						// Чистим память
	}