#pragma once
#include <string>

	// ������� ��������� ���������� � ������ �������� �������
	std::string similar_disc_kaf(std::string Discipline)
		{
			if (Discipline == "�������������� ���������" || Discipline == "������������ �������" || Discipline == "���������� �������")
				{
					return "��-1";
				}
			if (Discipline == "������������� ���������" || Discipline == "�������������� ������" || Discipline == "�������� �������" || Discipline == "��������� � ���������������� ���������" || Discipline == "�������� �������")
				{
					return "��-1";
				}
			if (Discipline == "���������� ����������")
				{
					return "��-2";
				}
			if (Discipline == "������")
				{
					return "��-4";
				}
			if (Discipline == "�����")
				{
					return "��-5";
				}
			if (Discipline == "������ �������������� � ������������ �����������")
				{
					return "��-7";
				}
			if (Discipline == "�������������� � ������������ �������������" || Discipline == "����������������� ������������� � �������")
				{
					return "��-11";
				}
			if (Discipline == "������ ����������" || Discipline == "������������ ������ ���������������� ���������" || Discipline == "����������� ����������� �������")
				{
					return "��-12"; // ���������
				}
			else
				{
					return "NOT STATED";
				}
		}
	std::string similar_kaf_organization(std::string kafedra)
		{
			if (kafedra == "��-1" || kafedra == "��-2" || kafedra == "��-1"|| kafedra == "��-12")
				{
					return "��� ���������";
				}
			else
				{
					return "NOT STATED";
				}
		}