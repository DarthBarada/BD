#pragma once
#include <exception>
#include <string>
#include <iostream>
#include <filesystem>

class wrong_enter:public std::exception
	{
		public:
			virtual const char* what() const noexcept
				{
					return "\nWrong enter!\n";
				}
	};

class file_not_exists :public std::exception
	{
		public:
			virtual const char* what() const noexcept
				{
					return "\nFile don't exist!\n";
				}
	};

class txt_exist :public std::exception
	{
		public:
			virtual const char* what() const noexcept
				{
					return "\nIt's not txt file!\n";
				}
	};

class data_exist :public std::exception
	{
		public:
			virtual const char* what() const noexcept
				{
					return "\nHasn't data!\n";
				}
	};

template <typename T>
bool cin(T* item)
	{
		try
			{
				std::cin >> item;
				if (std::cin.fail())
					{
						wrong_enter a;
						std::cin.clear();
						std::cin.ignore(32767, '\n');

						throw a;
					}
			}
		catch (std::exception &exp)
			{
				std::cout << exp.what();
				return false;
			}
		return true;
	}

bool is_exist(std::string way)
	{
		try
			{
				if (!std::experimental::filesystem::exists("Data/" + way))
					{
						file_not_exists a;
						throw a;
					}
			}
		catch (...)
			{
				return false;
			}
		return true;
	}

bool is_txt(std::string destination)
	{
		std::string txt;
		try
			{
				if (destination.size() >= 4)
					{
						for (int i = destination.size() - 4; i<int(destination.size()); i++)
							{
								txt += destination.at(i);
							}
						if (txt != ".txt")
							{
								txt_exist a;
								throw a;
							}
					}
				else
					{
						txt_exist b;
						throw b;
					}
			}
		catch (...)
			{
				return false;
			}
		return true;
	}

bool have_data(std::string destination)
	{
		std::string txt;
		try
			{
				if (destination.size() >= 5)
					{
						for (int i =0; i<5; i++)
							{
								txt += destination.at(i);
							}
						if (txt != "Data/")
							{
								data_exist a;
								throw a;
							}
					}
				else
					{
						data_exist b;
						throw b;
					}
			}
		catch (...)
			{
				return false;
			}
		return true;
	}

bool cin(int& item)
	{
		try
			{
				std::cin >> item;
				if (std::cin.fail())
					{
						wrong_enter a;
						std::cin.clear();
						std::cin.ignore(32767, '\n');

						throw a;
					}
			}
		catch (std::exception &exp)
			{
				std::cout << exp.what();
				return false;
			}
		return true;
	}