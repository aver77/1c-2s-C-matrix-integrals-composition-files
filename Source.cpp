#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <iomanip>
using namespace std;

void checkdegree(int &n);
void parameters(double &a, double &b);
double integral(const int n, const double x, double &power);
char finish_Programm();

int main()
{
	setlocale(LC_ALL, "ru");
	bool flag;
	do 
	{
		flag = true;

		int n;
		checkdegree(n);

		double a, b;
		parameters(a, b);

		if (a != b)
		{
			if (a > b) 
			{
				swap(a, b);
			}
			double power;
			cout << "Верхней границей интегрирования было выбрано: " << b << endl;
			cout << "Нижней границей интегрирования было выбрано: " << a << endl;
			cout << "Результат: " << setprecision(10) << integral(n, b, power) - integral(n, a, power) << endl;
		}
		else cout << "Верхняя и нижняя границы интегрирования равны, поэтому результат равен 0" << endl;

		char Exit = finish_Programm();

		if (Exit == 'y' || Exit == 'Y')
		{
			flag = false;
		}

	} while (flag);

	return 0;
}
void checkdegree (int &n)
{
	cout << "Введите степень n в диапазоне [1,+infinity)" << endl;
	cin >> n;
	short Error = 0;
	while (Error == 0)
	{
		if (n<0)
		{
			cout << "Ошибка ввода,введите диапазон от 1 до бесконечности" << endl;
			cin >> n;
		}
		else
		{
			Error = 1;
		}
	}
}
void parameters(double &a, double &b)
{
	cout << "Введите пределы интегрирования в диапазоне (0,+infinity)" << endl;
	cin >> a >> b;
	short Error = 0;
	while (Error == 0)
	{
		if (a < 0 || b < 0)
		{
			cout << "Ошибка ввода,введите каждый предел в диапазоне от 0 до бесконечности" << endl;
			cin >> a >> b;
		}
		else
		{
			Error = 1;
		}
	}
}
double integral(const int n, const double x,double &power)
{
	switch (n)
	{
		case 1:
		{
			power = log(x);
			return x*log(x) - x;
			break;
		}
		default:
		{
			double Int = n*integral(n - 1, x, power);
			power *= log(x);
			return (-Int)+(power*x);
			//return Int;
			break;
		}
	}
}
char finish_Programm()
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