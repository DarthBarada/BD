#pragma once
#include "Save_Info.h"
#include "Get Info.h"
#include "KOHCTPYKTOP.h"
#include "Print.h"

#include "Branch_Faculties.h"
#include "Base_Faculties.h"
#include "Exeption.h"
#include "Facult.h"

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>

inline void shapka()
	{
		std::cout << "\t\t\tData Base"<<std::endl<<"Author: Dmitry Mitrofanov \t\t Group: IC8-23\n"<<"Bauman Moscow State University\n"<<"ver: 0.0.0\n";
	}

inline void shapka2()
	{
		std::cout << "\t\tEnter command: ";
		std::cout << "\n\tTo see more commands enter \"help\"\n";
	}

void Note1()
	{
		std::cout << "\nTo switch search use buttons up and down; to exit press Esc; to save press \"Space\"): \n";
	}

namespace fs = std::experimental::filesystem;

class console: KOHCTPYKTOP, print, Info
	{
		std::vector <facult> bufferzone;
		std::string command;
		std::string destination;
		int pos=0;

	public:

		~console()
			{
				init();
				branch_faculties.clear();
				base_faculties.clear();
				command.clear();
				destination.clear();
				save_other(bufferzone, "Data/temp.txt");
			}


		void init()
			{
				bufferzone.resize(base_faculties.size() + branch_faculties.size());
				std::copy(base_faculties.begin(), base_faculties.end(), bufferzone.begin());
				std::copy(branch_faculties.begin(), branch_faculties.end(), bufferzone.begin()+base_faculties.size());
			}
			
		void loop()
			{		
				shapka2();
				while (true)
					{
						enter(); accord_comm();
					}
			}

		void enter()
			{
				pos = 0;
				command.clear();
				destination.clear();

				std::cout << "\n>> ";
				char znak;
				znak = _getch();
				while (znak != '\r')
					{
						std::cout << znak;
						if (znak != ' ')
							{
								if (znak != '\b')
									{
										switch (pos)
											{
												case 0:command += znak; break;
												default:destination += znak;
											}
									}
								else
									{
										if (!destination.empty())
											{
												destination.pop_back();
											}
										else
											{
												pos = 0;
												if (!command.empty())
													{
														command.pop_back();
													}
											}
										system("cls");
										shapka2();
										std::cout << ">> " + command;
										if (!destination.empty())
											{
												std::cout << " " + destination;
											}
									}
							}
						else
							{
								pos++;
								if (!destination.empty())
									{
										destination += ' ';
									}
							}
						znak = _getch();
					}
			}

		void accord_comm()
			{
				if (command == "help" || command == "commands")
					{
						std::cout << "\n\t\tCommands\n\n-create <facult/faculties> (to create facult or faculties)\n-all or show all\n-save\n-see (to see all)\n-search <what>\n-sort <type>\n-change\n-info\n-man <command> (to see more about command)";
					}
				if (command == "create")
					{
						if (destination == "facult")
							{
								create_facult();
							}
						else if (destination=="faculties")
							{
								std::cout << "\nEnter count of faculties: ";
								std::cin >> pos;
								bufferzone = create_faculties(pos);
							}

						std::cout << "Want save it (1-yes,0-no)?";
						pos = 0;
						cin(pos);
						if (pos == 1)
							{
								save_other(bufferzone, "Data/created.txt");/**/
							}
						sort();
					}
				if (command == "open")
					{
						get_info(destination);
						print_all(base_faculties,branch_faculties);
					}
				if (command == "all" || command+' '+ destination == "show all")
					{
						for (const auto & entry : fs::directory_iterator("Data/"))
						std::cout << std::endl << std::endl << entry.path() << std::endl;
					}
				if (command == "save")
					{
						init();
						if (destination.empty())
							{
								save_other(bufferzone, "Data/Faculties.txt");
							}
						else
							{
								if (is_txt(destination))
									{
										save_other(bufferzone, "Data/" + destination);
									}
								else
									{
										
									}
							}
					}
				if (command == "search")
					{
						int pos=1; // Отвечает за правило выборки 1 - facult, 2 - discipline, 3 - HYK 
						std::vector <facult> temp;
						init();

						Note1();
						std::cout << "status: facult\n";
						while (!GetAsyncKeyState(0x1B))
							{
								system("cls");
								Note1();
								if (GetAsyncKeyState(VK_UP))
									{
										temp.clear();
										if (pos > 1)
											{
												pos --;
												std::cout << std::endl;
											}
										if (pos == 1)
											{
												std::cout << "status: facult\n";
											}
										else if (pos == 2)
											{
												std::cout << "status: discipline\n";
											}
										else
											{
												std::cout << "status: HYK\n";
											}
									}
								else if (GetAsyncKeyState(VK_DOWN))
									{
										temp.clear();
										if (pos < 3)
											{
												pos++;
												std::cout << std::endl;
											}
										if (pos == 1)
											{
												std::cout << "status: facult\n";
											}
										else if (pos == 2)
											{
												std::cout << "status: discipline\n";
											}
										else
											{
												std::cout << "status: HYK\n";
											}
									}
								if (GetAsyncKeyState(0x20))
									{
										save_other(temp, "Data/search.txt");
										std::cout << "Saved into Data/search.txt ";
										Sleep(1000);
									}
								if (pos == 1)
									{
										for (int i = 0; i<int(bufferzone.size()); i++)
											{
												if (bufferzone.at(i).get_facult_name()==destination)
													{
														print_just_facult(bufferzone.at(i));
														temp.push_back(bufferzone.at(i));
													}
											}
									}
								else if(pos == 2)
									{
										for (int i = 0; i<int(bufferzone.size()); i++)
											{
												for (int j = 0; j<int(bufferzone.at(i).get_disciplines()->size()); j++)
													{
														if (bufferzone.at(i).get_disciplines()->at(j).get_name() == destination)
															{
																print_facult(bufferzone.at(i));
																temp.push_back(bufferzone.at(i));
															}
													}
											}
									}
								else
									{
										for (int i = 0; i<int(bufferzone.size()); i++)
											{
												if (bufferzone.at(i).get_HYK() == destination)
													{
														print_facult(bufferzone.at(i));
														temp.push_back(bufferzone.at(i));
													}
											}
									}
								_getch();_getch();
							} 
					}
				if (command == "sort")
					{
						init();
						std::cout << "\nEnter type of sort (1-name of facult / 2- count of departments): ";
						std::cin >> pos;
						if (pos == 1)
							{
								for (int i = 0; i<double(bufferzone.size()) / 2; i++)
									{
										for (int j = i; j<int(bufferzone.size()); j++)
											{
												if (bufferzone.at(i).get_facult_name() < bufferzone.at(j).get_facult_name())
													{
														std::swap(bufferzone.at(i), bufferzone.at(j));
													}
											}
									}
							}
						if (pos == 2)
							{
								for (int i = 0; i<double(bufferzone.size()) / 2; i++)
									{
										for (int j = i; j<int(bufferzone.size()); j++)
											{
												if (bufferzone.at(i).get_count_of_kaf() < bufferzone.at(j).get_count_of_kaf())
													{
														std::swap(bufferzone.at(i), bufferzone.at(j));
													}
											}
									}
							}
						print_just_facult(bufferzone);

						std::cout << "\nWant save it (1-yes,0-no)?";
						pos = 0;
						cin(pos);
						if (pos == 1)
							{
								save_other(bufferzone, "Data/sorted.txt");
							}
						sort();
					}
				if (command == "change")
					{
						init();
						std::cout << "\n\n";
						std::cout << std::left << "\n"<<std::setw(4)<<"№"<< std::setw(10) << "Faculty" << std::setw(50) << "HYK" << std::setw(24) << "Number of departments"<< "\n";
						for (int i = 0; i<int(bufferzone.size()); i++)
							{
								std::cout <<std::setw(2)<< i + 1<<": ";
								print_just_facult(bufferzone.at(i));
							}	
						std::cout << "What facult you want to change: ";
						std::cin >> pos;
						pos--;
						system("cls");
						print_facult(bufferzone.at(pos));
						std::cout << "\nNote: to delete facult enter \"delete\"; to change disciplines enter  \"change\"\n>> ";
						std::cin >> command;
						if (command == "delete")
							{
								bufferzone.erase(bufferzone.begin()+pos);
								base_faculties.clear(); branch_faculties.clear();
								sort();
								system("cls");
								print_just_facult(bufferzone);
							}
						else if (command == "change")
							{
								system("cls");
								print_discs(bufferzone.at(pos));
								std::cout << "Note: To add new discipline enter \"add\"; to delete discipline enter \"delete\"";
								std::cin >> command;
								if (command == "add")
									{
										bufferzone.at(pos).get_disciplines()->push_back(create_discipline());
									}
								else if (command == "delete")
									{
										std::cout << "Enter pos: ";
										std::cin >> pos;
										pos--;
										bufferzone.at(pos).get_disciplines()->erase(bufferzone.at(pos).get_disciplines()->begin() + pos);
									}
							}
					}
				if (command == "man")
					{
						std::cout << std::endl;
						if (destination == "create")
							{
								std::cout << "-create facult \t\tЭта команда позволяет создать 1 факультет или несколько.\n-create faculties\n";
							}
						if (destination == "open")
							{
								std::cout << "-open <file.txt> \t\tЭта команда нужна для открытия файла с расширением .txt.\n";
							}
						if (destination == "all"|| destination == "show all")
							{
								std::cout << "-all\t\tЭта команда нужна для просмотра файлов в папке Data.\n-show all\n";
							}
						if (destination == "save")
							{
								std::cout << "-save\t\tЭта команда нужна для сохранения информации о базовых и отраслевых факультетах.\n";
							}
						if (destination == "search")
							{
								std::cout << "-search <string>\t\tЭта команда нужна для нахождения записей по названию факультета или НУК, либо по дисциплинам.\n";
							}
						if (destination == "sort")
							{
								std::cout << "-sort \t\tЭта команда нужна для сортировки БД по названию факультета или по количеству кафедр.\n";
							}
						if (destination == "change")
						{
							std::cout << "-change \t\tЭта команда позволяет удалить факультет или изменять его дисциплины\n";
						}
					}
				if (command == "info")
					{
						std::cout << std::endl;
						shapka();
					}
				if (command == "see")
					{
						init();
						print_facults(bufferzone);
					}

			}

		void sort()
			{
				branch_faculties.clear();
				base_faculties.clear();
				for (int i = 0; i<int(bufferzone.size()); i++)
					{
						if (bufferzone.at(i).get_facult_name() == "РКТ" || bufferzone.at(i).get_facult_name() == "АК" || bufferzone.at(i).get_facult_name() == "ПС" || bufferzone.at(i).get_facult_name() == "РТ" || bufferzone.at(i).get_facult_name() == "ОЭП")
							{
								branch_faculties.push_back(bufferzone.at(i)); // Отраслевые факультеты
							}
						else
							{
								base_faculties.push_back(bufferzone.at(i)); // Базовые факультеты
							}
					}
			}

	};