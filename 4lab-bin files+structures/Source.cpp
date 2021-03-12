#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

struct AEROFLOT
{
	char destination[30];
	int number;
	char type[30];

	void Reading_Method(ifstream &fin)
	{
		fin >> destination >> number >> type;
	}

	void Print_Method()
	{
		cout << destination << " " << number << " " << type << " " << endl;
	}

	int Compare_Method(AEROFLOT aeroflot)
	{
		return strcmp(destination, aeroflot.destination);
	}
};

void Read_From_Txt_File(AEROFLOT*& a, ifstream& fin, int& n);
void Print_To_Binary_File(AEROFLOT* a, int n, ofstream& out);
void Sort_Txt_File(AEROFLOT* a, int n);
bool Read_From_Binary_File(ifstream& bin, char* certain_type);

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	ifstream fin("inp1.txt");

	int n;

	AEROFLOT *a = NULL;

	if (fin.is_open())
	{
		cout << "Текстовый файл успешно открыт" << endl;
		Read_From_Txt_File(a, fin, n);
		Sort_Txt_File(a, n);

		for (int i = 0; i < n; i++) // КОНТРОЛЬНАЯ ПЕЧАТЬ МАССИВА (ПОТОМ МОЖНО УБРАТЬ)
			a[i].Print_Method();

		cout << "Введите имя бинарного файла" << endl;
		string path;
		cin >> path;
		ofstream out(path.c_str(), ios::binary);
		Print_To_Binary_File(a, n, out);
		out.close();

		cout << "Считывание данных из бинарного файла:" << endl;
		ifstream bin(path.c_str(), ios::binary);

		cout << "Задайте тип самолета для поиска его пунктов назначения и номеров рейсов:" << endl;
		char certain_type[30];
		cin >> certain_type;

		if (!Read_From_Binary_File(bin, certain_type)) cout << "Самолетов с указанным типом не найдено" << endl;

		delete[] a;
		fin.close();
		bin.close();
	}
	else
	{
		cout << "Ошибка открытия текстового файла" << endl;
	}

	cin.ignore().get();
	return 0;
}

void Read_From_Txt_File(AEROFLOT*& a, ifstream& fin, int& n) //функция,в которой так же используем метод считывания из текстового файла
{
	fin >> n;
	a = new AEROFLOT[n];
	for (int i = 0; i < n; i++)
	{
		a[i].Reading_Method(fin);
	}
	cout << "Данные успешно считаны из текстового файла" << endl;
}

void Print_To_Binary_File(AEROFLOT* a, int n, ofstream& out)
{
	if (out.is_open())
	{
		cout << "Бинарный файл успешно открыт" << endl;
		for (int i = 0; i < n; i++)
		{
			out.write((char*)&a[i], sizeof(a[i]));
		}
	}
	else
	{
		cout << "Ошибка открытия бинарного файла" << endl;
	}
	cout << "Данные успешно сохранены в бинарный файл" << endl;
}

void Sort_Txt_File(AEROFLOT* a, int n) //функция,являющаяся циклом для метода сравнения
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[i].Compare_Method(a[i + 1]) > 0)
			{
				swap(a[i], a[i + 1]);
			}
		}

	}
}

bool Read_From_Binary_File(ifstream& bin, char* certain_type)
{
	AEROFLOT aero;
	bool flag = false;
	while (!bin.eof())
	{
		bin.read((char*)&aero, sizeof(AEROFLOT));
		if (!bin.fail())
		{
			if (strcmp(aero.type, certain_type) == 0)
			{
				flag = true;
				aero.Print_Method();
			}
		}
	}
	return flag;
}
