#pragma once
#include "Facult.h"
#include <unordered_map>
#include <algorithm>

class branch_facult: public facult
	{
		int count_of_kaf_of_branchfaculties = 0; // Count of departments 
	protected:
		std::vector <facult> branch_faculties;
	public:

		// Counter of departments into branch faculties
		/*void counter()
			{
				for (int i = 0; i<int(branch_faculties.size()); i++)
					{
						count_of_kaf_of_branchfaculties += branch_faculties.at(i).get_count_of_kaf();
					}
			}*/
	};