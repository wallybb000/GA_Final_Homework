// GA_Final_Homework.cpp: 主要專案檔。

#include "stdafx.h"
#include "Chromosome.h"
#include "GA.h"

using namespace std;
using namespace System;
using namespace System::IO;

vector <vector<int>> Questionnaire;
vector <vector<int>> TeacherLesson;
int main(array<System::String ^> ^args)
{

	String^ path = "test.txt";
 StreamWriter^ sw = File::CreateText(path);

 

		
	StreamReader strReader("期末作業參數.txt");

	String ^ bufString;
	if (bufString = strReader.ReadLine())
	{
		int length = bufString->Length;
		int teacherCount = (length + 2) / 21;
		for (int i = 0; i < teacherCount; i++)
		{
			TeacherLesson.push_back(std::vector<int>());
			for (int j = 0; j < 3; j++)
				TeacherLesson[i].push_back(Convert::ToInt16(bufString[i * 21 + j * 7 + 4]) - 48);
		}
	}
	if (bufString = strReader.ReadLine())
	{
		int length = bufString->Length;
		int teacherCount = (length + 2) / 15;
		for (int i = 0; i < teacherCount; i++)
		{
			Questionnaire.push_back(std::vector<int>());
			for (int j = 0; j < 3; j++)
			{
				int a = (Convert::ToInt16(bufString[i * 15 + 2 + j * 4]) - 48 - 1);//1~5 >>0~4
				int b = (Convert::ToInt16(bufString[i * 15 + 2 + j * 4 + 2]) - 48);

				Questionnaire[i].push_back(a + b*WEAK_LENGTH*2);
			}
		}

	}

	GA mGA;

	for (int generation = 0; generation < 10000; generation++)
	{

		int Max=mGA.Fitness();


		mGA.Select();
		mGA.Crossover();
		mGA.Mutation();
		sw->WriteLine(Convert::ToString(Max));
		Console::WriteLine(Convert::ToString(Max));
	}
	sw->Close();

    Console::WriteLine(L"Hello World");
    return 0;
}
