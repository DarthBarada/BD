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
		std::cout << "\t\t\tData Base"<<std::endl<<"Author: Dmitry Mitrofanov \t\t Group: IC8-23\n"<<"Bauman Moscow State University\n"<<"ver: 0.1.0\n";
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

class console: KOHCTPYKTOP, public print, Info
	{
		std::multimap <std::string,Facult> bufferzone;
		std::string command;
		std::string destination;
		int pos=0;

	public:

		~console()
			{
				init();
				get_base_faculties()->clear();
				get_branch_faculties()->clear();
				destination.clear();
				if (!bufferzone.empty())
					{
						std::cout << "\nDo you want to save information [yes/no]?\n>> ";
						std::cin >> command;
						if (command == "yes")
							{
								if (!is_exist("temp.txt"))
									{
										save_other(bufferzone, "Data/temp.txt");
										std::cout << "Saved into Data/temp.txt ";
									}
								else
									{
										pos = 0;
										while (is_exist("temp" + std::to_string(pos) + ".txt"))
											{
												pos++;
											}
										save_other(bufferzone, "Data/temp" + std::to_string(pos) + ".txt");
										std::cout << "Saved into  Data/temp" + std::to_string(pos) + ".txt";
									}
							}
					}
				bufferzone.clear();
				command.clear();
			}

		void init()
			{
				bufferzone.clear();
				for (auto i = get_base_faculties()->begin(); i != get_base_faculties()->end(); i++)
					{
						bufferzone.insert(*i);
					}
				for (auto i = get_branch_faculties()->begin(); i != get_branch_faculties()->end(); i++)
					{
						bufferzone.insert(*i);
					}
			}
			
		void loop()
			{		
				shapka2();
				do
					{
						enter();
				} while (accord_comm());
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
		
		bool accord_comm()
			{
				if (command == "help" || command == "commands")
					{
						std::cout << "\n\t\tCommands\n\n-create <facult/faculties> (to create facult or faculties)\n-all or show all\n-save\n-see (to see all)\n-search <what>\n-sort <type>\n-change\n-info\n-man <command> (to see more about command)\n-clear (to clear screen)\n-close (to exit)";
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

								std::cout << "Want save it (1-yes,0-no)?";
								pos = 0;
								cin(pos);
								if (pos == 1)
									{
										if (!is_exist("created.txt"))
											{
												save_other(bufferzone, "Data/created.txt");
												std::cout << "Saved into Data/created.txt ";
											}
										else
											{
												pos = 0;
												while (is_exist("created" + std::to_string(pos) + ".txt"))
													{
														pos++;
													}
												save_other(bufferzone, "Data/created" + std::to_string(pos) + ".txt");
												std::cout << "Saved into  Data/created" + std::to_string(pos) + ".txt";
											}
									}
							}
						sort();
					}
				if (command == "open")
					{
						get_info(destination);
						print_all(*get_base_faculties(),*get_branch_faculties());
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
								if (!is_exist("Faculties.txt"))
									{
										saver();
									}
								else
									{
										pos = 0;
										while (is_exist("Faculties"+std::to_string(pos)+".txt"))
											{
												pos++;
											}
										save_other(bufferzone, "Data/Faculties"+std::to_string(pos)+".txt");
									}
							}
						else
							{
								if (is_txt(destination))
									{
										save_other(bufferzone, "Data/" + destination);
									}
							}
					}
				if (command == "search")
					{
						if (!destination.empty())
							{
								int pos = 1; // Отвечает за правило выборки 1 - facult, 2 - discipline, 3 - HYK 
								std::multimap <std::string, Facult> temp;
								init();

								Note1();
								std::string status = "facult";
								while (!GetAsyncKeyState(0x1B))
									{
										system("cls");
										Note1();
										std::cout << "status: " + status+'\n';
										if (pos == 1)
											{
												for (auto i = bufferzone.begin(); i != bufferzone.end(); i++)
													{
														if (i->second.get_facult_name() == destination)
															{
																print_just_facult(i->second);
																temp.insert(std::pair<std::string, Facult>(i->second.get_facult_name(), i->second));
															}
													}
											}
										if (pos == 2)
											{
												for (auto i = bufferzone.begin(); i != bufferzone.end(); i++)
													{
														for (auto j = i->second.get_disciplines()->begin(); j != i->second.get_disciplines()->end(); j++)
															{
																if (j->second.get_name() == destination)
																	{
																		print_just_facult(i->second);
																		temp.insert(std::pair<std::string, Facult>(i->second.get_facult_name(), i->second));
																	}
															}
													}
											}
										if (pos == 3)
											{
												for (auto i = bufferzone.begin(); i != bufferzone.end(); i++)
													{
														if (i->second.get_HYK() == destination)
															{
																print_just_facult(i->second);
																temp.insert(std::pair<std::string, Facult>(i->second.get_facult_name(), i->second));
															}
													}
											}
										if (GetAsyncKeyState(VK_UP))
											{
												temp.clear();
												if (pos > 1)
													{
														pos--;
														std::cout << std::endl;
													}
												if (pos == 1)
													{
														status= "facult";
													}
												if (pos == 2)
													{
														status = "discipline";
													}
												if (pos == 3)
													{
														status = "HYK";
													}
											}
										if (GetAsyncKeyState(VK_DOWN))
											{
												temp.clear();
												if (pos < 3)
													{
														pos++;
														std::cout << std::endl;
													}
												if (pos == 1)
													{
														status = "facult";
													}
												if (pos == 2)
													{
														status = "discipline";
													}
												if (pos == 3)
													{
														status = "HYK";
													}
											}
										if (GetAsyncKeyState(0x20))
											{
												if (!temp.empty())
													{
														if (!is_exist("search.txt"))
															{
																save_other(temp, "Data/search.txt");
																std::cout << "Saved into Data/search.txt\nTo update page use up and down.";
															}
														else
															{
																pos = 0;
																while (is_exist("search" + std::to_string(pos) + ".txt"))
																	{
																		pos++;
																	}
																save_other(temp, "Data/search" + std::to_string(pos) + ".txt");
																std::cout << "Saved into  Data/search" + std::to_string(pos) + ".txt\nTo update page use up and down.";
															}
													}
												Sleep(1000);
											}
										std::cout << std::endl;
										_getch();
									}
								system("cls");
								shapka2();
							}
						else
							{
								std::cout << "\nNeed argument!\n";
							}
					}
				if (command == "sort")
					{
						init();
						std::multimap <std::string, Facult>* temp_map= new std::multimap <std::string, Facult>;
						std::cout << "\nEnter type of sort (1-name of facult / 2- count of departments): ";
						std::cin >> pos;
						if (pos == 1)
							{
								for (auto i = bufferzone.begin(); i != bufferzone.end(); i++)
									{
										temp_map->insert(std::pair <std::string, Facult>(i->second.get_facult_name(), i->second));
									}
							}
						if (pos == 2)
							{
								for (auto i = bufferzone.begin(); i != bufferzone.end(); i++)
									{
										if (i->second.get_count_of_kaf() < 10)
											{
												temp_map->insert(std::pair <std::string, Facult>("0"+std::to_string(i->second.get_count_of_kaf()), i->second));
											}
										else
											{
												temp_map->insert(std::pair <std::string, Facult>(std::to_string(i->second.get_count_of_kaf()), i->second));
											}
									}
							}
						bufferzone.clear(); bufferzone = *temp_map;
						delete temp_map;
						print_just_facult(bufferzone);

						std::cout << "\nWant save it (1-yes,0-no)? ";
						pos = 0;
						cin(pos);
						if (pos == 1)
							{
								if (!is_exist("sorted.txt"))
									{
										save_other(bufferzone, "Data/sorted.txt");
										std::cout << "Saved into Data/sorted.txt ";
									}
								else
									{
										pos = 0;
										while (is_exist("sorted" + std::to_string(pos) + ".txt"))
											{
												pos++;
											}
										save_other(bufferzone, "Data/sorted" + std::to_string(pos) + ".txt");
										std::cout << "Saved into  Data/sorted" + std::to_string(pos) + ".txt";
									}
							}
						sort();
					}
				if (command == "change")
					{
						init();
						pos = 0;
						std::cout << "\n\n";
						std::cout << std::left << "\n"<<std::setw(4)<<"№"<< std::setw(10) << "Faculty" << std::setw(50) << "HYK" << std::setw(24) << "Number of departments"<< "\n";
						for (auto i = bufferzone.begin(); i!= bufferzone.end(); i++)
							{
								std::cout <<std::setw(2)<< pos + 1<<": ";
								print_just_facult(i->second);
								pos++;
							}	
						std::cout << "What facult you want to change: ";
						std::cin >> pos;
						pos--;
						system("cls");
						auto tempit = bufferzone.begin();
						for (int i = 0; i < pos; i++)
							{
								tempit++;
							}
						print_facult(tempit->second);
						std::cout << "\nNote: to delete facult enter \"delete\"; to change disciplines enter  \"change\"\n>> ";
						std::cin >> command;
						if (command == "delete")
							{
								bufferzone.erase(tempit);
								system("cls");
								print_just_facult(bufferzone);
							}
						else if (command == "change")
							{
								system("cls");
								print_discs(tempit->second);
								std::cout << "Note: To add new discipline enter \"add\"; to delete discipline enter \"delete\"";
								std::cin >> command;
								if (command == "add")
									{
										if (similar_facult(tempit->second.get_facult_name()) == 1)
											{
												tempit->second.get_disciplines()->insert(std::pair<std::string, discipline>(create_discipline().get_kafedra(), create_discipline()));
											}
										else if (similar_facult(tempit->second.get_facult_name()) == 2)
											{
												tempit->second.get_disciplines()->insert(std::pair<std::string, discipline>(create_discipline().get_organization(), create_discipline()));
											}
									}
								else if (command == "delete")
									{
										std::cout << "Enter pos: ";
										std::cin >> pos;
										pos--;
										auto tempit2 = tempit->second.get_disciplines()->begin();
										for (int i = 0; i < pos; i++)
											{
												tempit2++;
											}
										tempit->second.get_disciplines()->erase(tempit2);
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
								std::cout << "-save <  or <way>.txt >\t\tЭта команда нужна для сохранения информации о базовых и отраслевых факультетах.\n\t\t\t\tВ качестве аргумента принимет ничего или имя файла с .txt на конце.";
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
				if (command == "close")
					{	
						return false;
						std::cout << std::endl;
					}
				if (command == "clear")
					{
						system("cls");
						shapka2();

					}
				return true;
			}

		void sort()
			{
				get_base_faculties()->clear();
				get_branch_faculties()->clear();
				for (auto i = bufferzone.begin(); i!=bufferzone.end(); i++)
					{
						if (similar_facult(i->second.get_facult_name()) == 1)
							{
								get_base_faculties()->insert(*i); // Базовые факультеты
							}
						else if(similar_facult(i->second.get_facult_name()) == 2)
							{
								get_branch_faculties()->insert(*i); // Отраслевые факультеты
							}
					}
			}

	};