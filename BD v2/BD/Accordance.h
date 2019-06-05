#pragma once
#include <string>

// Функция оределяет кафедру по назвинию дисциплины 
	std::string similar_disc_kaf(std::string Discipline)
		{
			if (Discipline == "Начертательная геометрия" || Discipline == "Компьютерная графика" || Discipline == "Инженерная графика")
				{
					return "РК-1";
				}
			if (Discipline == "Аналитическая геометрия" || Discipline == "Математический анализ" || Discipline == "Линейная алгебра" || Discipline == "Интегралы и дифференциальные уравнения" || Discipline == "Линейная алгебра")
				{
					return "ФН-1";
				}
			if (Discipline == "Прикладная математика")
				{
					return "ФН-2";
				}
			if (Discipline == "Физика")
				{
					return "ФН-4";
				}
			if (Discipline == "Химия")
				{
					return "ФН-5";
				}
			if (Discipline == "Основы электротехники и промышленной электроники")
				{
					return "ФН-7";
				}
			if (Discipline == "Математическое и компьютерное моделирование" || Discipline == "Суперкомпьютерное моделирование в технике")
				{
					return "ФН-11";
				}
			if (Discipline == "Теория управления" || Discipline == "Качественная теория дифференциальных уравнения" || Discipline == "Многомерные управляемые системы")
				{
					return "ФН-12"; // Дополнить
				}
			else
				{
					return "NOT STATED";
				}
		}

// Функция оределяет организацию по назвинию кафедры 
	std::string similar_kaf_organization(std::string kafedra)
		{
			if (kafedra == "РК-1" || kafedra == "МТ-2" || kafedra == "СМ-1"|| kafedra == "СМ-12")
				{
					return "РКК «Энергия»";
				}
			else
				{
					return "NOT STATED";
				}
		}
	/* Если имя факультета относится:
	1) к базовым факультетам, то возвращает 1,
	2) к  отраслевым факультетам, то 2
	3) иначе 0*/
	int similar_facult(std::string name)
		{
			if (name == "РКТ" || name == "АК" || name == "ПС" || name == "РТ" || name == "ОЭП")
				{
	// Если факультет - отраслевой возвращаем 2
					return 2; 
				}
			else
				{
	// Если факультет - базовый возвращаем 1
					return 1;
				}
			return 0;
		}