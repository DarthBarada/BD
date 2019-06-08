#pragma once

#include "Base_Faculties.h"
#include "Branch_Faculties.h"

class manager
	{	
	protected:
		std::map <std::string, base_facult> base_faculties;
		std::map <std::string, branch_facult> branch_faculties;

		base_facult temp_base_facult;
		branch_facult temp_branch_facult;

		std::multimap <std::string, facult*> bufferzone;

		std::multimap <std::string, facult*> searched;
		std::multimap <std::string, facult*> sorted;
		std::map <std::string, base_facult> created_base_faculties;
		std::map <std::string, branch_facult> created_branch_faculties;

	public:
		manager()
			{	}
		~manager()
			{
				base_faculties.clear();
				branch_faculties.clear();
				bufferzone.clear();
				searched.clear();
				sorted.clear();
			}
		/* Фукнция используется после создания и предназначена для отправки данных по факультетам */
		void transform()
			{
				bufferzone.clear();
				for (auto i = created_base_faculties.begin(); i != created_base_faculties.end(); i++)
					{
						base_faculties.insert(*i);
					}
				for (auto i = created_branch_faculties.begin(); i != created_branch_faculties.end(); i++)
					{
						branch_faculties.insert(*i);
					}
			}
	};