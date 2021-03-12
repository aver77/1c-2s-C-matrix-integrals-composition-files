#include <iostream>
#include <Windows.h>
#include <fstream>
#include <locale.h>
#include <string>
#include <conio.h>

using namespace std;

void Opened_file(char array_for_usual_words[][16], int &counter, int i, ifstream &fin, ofstream &fout);
void Input_to_matrix(char array_for_usual_words[][16], char word[], int &i);
void Output_for_pre_words(char word[], ofstream &fout);
void Output_for_usual_words(char array_for_usual_words[][16], int i, ofstream &fout);
void Print(int counter);

int main()
{
	cout << "Enter inp.txt - name of input file" << endl;
	string path;
	cin >> path;
	ifstream fin(path.c_str());
	cout << "Enter name of output file" << endl;
	cin >> path;
	ofstream fout(path.c_str());

	char array_for_usual_words[35][16]{ " " };

	int counter = 0, i = 0;
	if (fin.is_open() && fout.is_open())
	{
		Opened_file(array_for_usual_words, counter, i, fin, fout);
	}
	else
	{
		cout << "Opening file Error" << endl;
	}
	fin.close();
	fout.close();
	return 0;
}

void Opened_file(char array_for_usual_words[][16], int &counter, int i, ifstream &fin, ofstream &fout)
{
	cout << "File successfully opened" << endl;
	char word[16]{ " " };
	while (!fin.eof())
	{
		fin >> word;
		if (strncmp(word, "pre", 3) == 0)
		{
			Output_for_pre_words(word, fout);
			counter++;
		}
		else
		{
			Input_to_matrix(array_for_usual_words, word, i);
		}
	}
	Print(counter);
	Output_for_usual_words(array_for_usual_words, i, fout);
}

void Input_to_matrix(char array_for_usual_words[][16], char word[], int &i)
{
	strcpy_s(array_for_usual_words[i], 15, word);
	i++;
}

void Output_for_pre_words(char word[], ofstream &fout)
{
	fout << word << endl;
}

void Output_for_usual_words(char array_for_usual_words[][16], int i, ofstream &fout)
{
	for (unsigned short k = 0; k < i; k++)
	{
		fout << array_for_usual_words[k] << endl;
	}
}

void Print(int counter)
{
	if (counter == 0)
	{
		cout << "There are no words starting with 'pre'" << endl;
	}
	else
	{
		cout << "There are words starting with 'pre'" << endl;
	}
}
