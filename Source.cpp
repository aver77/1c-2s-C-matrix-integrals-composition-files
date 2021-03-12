#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
using namespace std;

void MainMenu(); //выполнение задачи
void Sub_Menu(); //выбор заполнения матрицы
int CheckInput(int Choice); //Проверка номера задачи (ХОРОШАЯ ВЕЩЬ ДЛЯ ПРОВЕРКИ ВВЕДЕННОГО ЗНАЧЕНИЯ)
int CheckCondition(int n_1); //Проверка способа заполнения матрицы
short** Add_Memory(unsigned short n); //выделение памяти под матрицу
void Delete_Memory(short**& matrix, unsigned short n); //удаление памяти под матрицу
void Fill_Read(short** matrix, unsigned short n); //заполнение в ручную
void Fill_Random(short** matrix, unsigned short n); //заполнение случ образом
void Output_Matrix(short** matrix, unsigned short n); //ввод матрицы на экран
char Finish_Programm(); //завершение работы (ТОЖЕ ОЧЕНЬ ВАЖНАЯ ФУНКЦИЯ)
bool Solution1(short** matrix, unsigned short n); //решение первой задачи
int Solution2(short** matrix, unsigned short n); //решение второй задачи
void Check_Solution1_Negative(short** matrix, unsigned short n, int j, bool &flag); //отрицательные столбцы для 1 задачи
int Check_Solution1_Sum(short** matrix, unsigned short n, int j, int &count); //сумма элементов в столбце без отриц элементов для 1 задачи
int Check_Solution2_Before(short** matrix, unsigned short n, int &sum); //сумма над (парал) и на побочной диаг для 2 задачи
int Check_Solution2_After(short** matrix, unsigned short n, int &sum); //сумма под (парал) побочной диаг для 2 задачи

int main()
{
	setlocale(LC_ALL, "ru");
	int Choice;
	do {
		MainMenu();
		cin >> Choice;
		CheckInput(Choice);
		if (Choice != 3)
		{
			unsigned short n;
			cout << "Введите размерность квадратной матрицы" << endl;
			cin >> n;

			short** matrix = Add_Memory(n);

			Sub_Menu();

			int n_1;
			cin >> n_1;
			CheckCondition(n_1);

			switch (n_1)
			{
			case 1:
				Fill_Read(matrix, n);
				cout << endl;
				Output_Matrix(matrix, n);
				cout << endl;
				break;
			case 2:
				srand(time(0));
				Fill_Random(matrix, n);
				cout << endl;
				Output_Matrix(matrix, n);
				cout << endl;
				break;
			}

			if (Choice == 1)
			{
				if (!Solution1(matrix, n))
				{
					cout << "Во всех столбцах есть отрицательные элементы" << endl; 
				}
			}
			else
				if (Choice == 2)
				{
					cout << "Минимум среди сумм модулей элементов диагоналей,параллельных побочной диагонали матрицы=" << Solution2(matrix, n) << endl;
				}

			Delete_Memory(matrix, n);

			char Exit = Finish_Programm();

			if (Exit == 'y' || Exit == 'Y')
			{
				Choice = 3;
			}
		}

	} while (Choice != 3);

	return 0;
}

void MainMenu()
{
	cout << "1)Определить сумму элементов в тех столбцах,которые не содержат отрицательных элементов." << endl;
	cout << "2)Определить минимум среди сумм модулей элементов диагоналей,параллельных побочной диагонали матрицы." << endl;
	cout << "3)Завершить работу." << endl;
}
void Sub_Menu()
{
	cout << "1)Заполнение матрицы вручную." << endl;;
	cout << "2)Заполнение матрицы случаным образом." << endl;
}
int CheckInput(int Choice) 
{
	short Error = 0;
	while (Error == 0)
	{
		if (Choice > 3 || Choice < 1)
		{
			cout << "Ошибка ввода,введите ЦИФРУ от" << " " << 1 << " "  "до" << " " << 3 << endl;
		}
		else
		{
			Error = 1;
			return Choice;
		}
	}

}
int CheckCondition(int n_1)
{
	short Error = 0;
	while (Error == 0)
	{
		if (n_1 > 2 || n_1 < 1)
		{
			cout << "Ошибка ввода,введите ЦИФРУ от" << " " << 1 << " "  "до" << " " << 3 << endl;
		}
		else
		{
			Error = 1;
			return n_1;
		}
	}
}
short** Add_Memory(unsigned short n)
{
	short** matrix = new short*[n];
	for (short i = 0; i < n; i++)
	{
		matrix[i] = new short[n];
	}
	return matrix;
}
void Delete_Memory(short**& matrix, unsigned short n)
{
	for (short i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}
void Fill_Read(short** matrix, unsigned short n)
{
	cout << "Введите элементы матрицы размером: " << n << " х " << n << ":\n";
	for (short i = 0; i < n; i++)
	{
		for (short j = 0; j < n; j++)
			cin >> matrix[i][j];
	}
}
void Fill_Random(short** matrix, unsigned short n)
{
	for (short i = 0; i < n; i++)
		for (short j = 0; j < n; j++)
			matrix[i][j] = rand() % 50 - 25;
}
void Output_Matrix(short** matrix, unsigned short n)
{
	for (short i = 0; i < n; i++)
	{
		for (short j = 0; j < n; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}
}
char Finish_Programm()
{
	bool Error;
	char Exit;
	do
	{
		cout << "\nЗавершить работу? Y/N" << endl;
		Exit = _getche();
		cout << endl;
		Error = (Exit != 'Y' && Exit != 'y' && Exit != 'N' && Exit != 'n');
		if (Error) cout << "Выберите Y или N";
	} while (Error);
	return Exit;
}
bool Solution1(short** matrix, unsigned short n)
{
	int count = 0;
	bool flag;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) 
		{
			flag = true;
			Check_Solution1_Negative(matrix, n, j, flag);
			if (flag && i==n-1)
			{
				cout << "В столбце №" << j + 1 << " " << "Нет отрицательных элементов.Их сумма=" << Check_Solution1_Sum(matrix,n,j,count) << endl;
			}
		}
	}
	if (count == 0) 
	{
		return false;
	}
}
int Solution2(short** matrix, unsigned short n) 
{
	int sum = 0;
	int min = matrix[0][0];
	for (int p = n - 1; p >= 1 - n; p--)
	{
		Check_Solution2_Before(matrix, n, sum);
		Check_Solution2_After(matrix, n, sum);
		if (sum < min) {
			min = sum;
		}
	}
	return min;
}
void Check_Solution1_Negative(short** matrix, unsigned short n, int j,bool &flag)
{
	for (int i = 0; i < n; i++)
	{			
		if (matrix[i][j] < 0)
		{
			flag = false;
		}
	}
}
int Check_Solution1_Sum(short** matrix, unsigned short n, int j, int &count)
{
		int sum = 0;
		for (int i = 0; i < n; i++)
		{
			sum += matrix[i][j];
			if (matrix[i][j] > 0)
			{
				count++;
			}
		}
		return sum;
	}
int Check_Solution2_Before(short** matrix, unsigned short n, int &sum)
{
	int i, j;
	for (int p = n - 1; p >= 1 - n; p--)
	{
		if (p >= 0) {
			i = -1;
			sum = 0;
			for (j = n - p - 1; j >= 0; j--) {
				++i;
				sum += abs(matrix[i][j]);
			}
		}
	}
	return sum;
}
int Check_Solution2_After(short** matrix, unsigned short n, int &sum)
{
	int i, j;
	for (int p = n - 1; p >= 1 - n; p--)
	{
		j = n;
		sum = 0;
		for (i = abs(p); i < n; i++) {
			--j;
			sum += abs(matrix[i][j]);
		}
	}
	return sum;
}