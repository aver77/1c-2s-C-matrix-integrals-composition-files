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
			cout << "������� �������� �������������� ���� �������: " << b << endl;
			cout << "������ �������� �������������� ���� �������: " << a << endl;
			cout << "���������: " << setprecision(10) << integral(n, b, power) - integral(n, a, power) << endl;
		}
		else cout << "������� � ������ ������� �������������� �����, ������� ��������� ����� 0" << endl;

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
	cout << "������� ������� n � ��������� [1,+infinity)" << endl;
	cin >> n;
	short Error = 0;
	while (Error == 0)
	{
		if (n<0)
		{
			cout << "������ �����,������� �������� �� 1 �� �������������" << endl;
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
	cout << "������� ������� �������������� � ��������� (0,+infinity)" << endl;
	cin >> a >> b;
	short Error = 0;
	while (Error == 0)
	{
		if (a < 0 || b < 0)
		{
			cout << "������ �����,������� ������ ������ � ��������� �� 0 �� �������������" << endl;
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
		cout << "\n��������� ������? Y/N" << endl;
		Exit = _getche();
		cout << endl;
		Error = (Exit != 'Y' && Exit != 'y' && Exit != 'N' && Exit != 'n');
		if (Error) cout << "�������� Y ��� N";
	} while (Error);
	return Exit;
}