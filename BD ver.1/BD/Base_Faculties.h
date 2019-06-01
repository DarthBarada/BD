#pragma once
#include "Facult.h"
#include <unordered_map>
#include <algorithm>

class base_facult: public facult
	{
		int count_of_kaf_of_basefaculties=0; // Count of departments 

	protected:
		std::vector <facult> base_faculties;
	public:
		
		// Counter of departments into base faculties
	/*	void counter()
			{
				for (int i = 0; i<int(base_faculties.size()); i++)
					{
						count_of_kaf_of_basefaculties += base_faculties.at(i).get_count_of_kaf();
					}	
			}*/
	};