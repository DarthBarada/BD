#pragma once
#include <filesystem>
#include <fstream>

#include "Branch_Faculties.h"
#include "Base_Faculties.h"
#include "Exeption.h"
/*
	Это специальный класс, чтобы получать информацию из файла, обрабатывать её и отправлять её, соответственно по факуьлтетам.
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
				if (faculties.at(i).get_facult_name() == "РКТ" || faculties.at(i).get_facult_name() == "АК" || faculties.at(i).get_facult_name() == "ПС" || faculties.at(i).get_facult_name() == "РТ" || faculties.at(i).get_facult_name() == "ОЭП")
					{
						faculties.at(i).sortbyorg();
						branch_faculties.push_back(faculties.at(i)); // Отраслевые факультеты
					}
				else
					{
						faculties.at(i).sortbykaf(); // Сортируем дисциплины по кафедрам
						base_faculties.push_back(faculties.at(i)); // Базовые факультеты
					}
			}
	}

void Info:: get_info(std::string destination)
	{
		std::string line; // строка - буффер
		if (is_exist(destination))
			{
				std::ifstream in("Data/" + destination);
				if (in.is_open())
					{
						std::string buffer;
						int counter=0; // Счетчик, чтобы программа понимала в какой контейнер ей класть информауию 
						facult new_facult;
						discipline new_disc;

						while (std::getline(in, line))
							{
								//std::cout << line << std::endl; // Выводим полученную сторку
								
								for (int i = 0; i<int(line.size()); i++) // Парсим строку
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
																if (new_disc.get_name().empty())								// Если пустое имя, то изменяем его
																	{
																		new_disc.get_name() = buffer;
																	}
																else															// Иначе определяем количество преподавателей
																	{
																		new_disc.get_count_of_teachers()=stoi(buffer);
																		new_disc.accord();										// Находим соответствующую дисциплине кафедру и организацию
																		new_facult.get_disciplines()->push_back(new_disc);		// Добаляем дисциплину в вектор дисциплин
																		new_disc.get_name().clear();							// Чистим имя, чтобы можно не получить ошибку
																	}
															}
													}
												// Увеличивам счетчик,чтобы перейти к следующему элементу, чистим буффер
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
								faculties.clear(); /* Очищаем буффер, чтобы не хранить уже ненужную инфомацию */
							}
					}
				in.close();
			}
	}