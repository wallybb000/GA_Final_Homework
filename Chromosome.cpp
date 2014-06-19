#include "stdafx.h"
#include "Chromosome.h"

using namespace std;
using namespace System;
extern vector <vector<int>> Questionnaire;
extern vector <vector<int>> TeacherLesson;
Chromosome::Chromosome()
{
	Initialisation();
	CalculateFitness();
}

void Chromosome::Initialisation()
{
	Random rand;

	for (int i = 0; i < SUM_OF_TIME; i++)
	for (int j = 0; j < SUM_OF_ROOM; j++)
	{
		lessonlist[j][i] = { -1, -1, -1, -1 };
	}

	for (int i = 0; i < SUM_OF_LESSON; i++)
	{
		vector<int> selectable_Time;
		vector<int> selectable_Room;
		int selected_Time;
		int selected_Room;

		for (int time = 0; time < SUM_OF_TIME; time++)
		{
			bool isOK = true;

			//若j時段中無空教室 該時段不可用
			int temp = 0;
			for (int room = 0; room < 3; room++)
			if (lessonlist[room][time].no != -1)temp += 1;

			if (temp == 3)isOK = false;

			//若j時段中其他教室有重複年級 或重複老師 該時段不可用
			for (int room = 0; room < SUM_OF_ROOM; room++){
				if (TeacherLesson[i / 3][i % 3] == lessonlist[room][time].grade)isOK = false;
				if (lessonlist[room][time].teacher == i / 3)isOK = false;

			}
			if (isOK) selectable_Time.push_back(time);
		}

		if (selectable_Time.size()>0)
		{
			selected_Time = selectable_Time[rand.Next( selectable_Time.size())];

			for (int room = 0; room < SUM_OF_ROOM; room++)
			if (lessonlist[room][selected_Time].no == -1)selectable_Room.push_back(room);

			if (selectable_Room.size() != 0)
			{
				selected_Room = selectable_Room[rand.Next(selectable_Room.size())];
				lessonlist[selected_Room][selected_Time] = { i, i /3, i %3, TeacherLesson[i / 3][i % 3] };
				location[i] = { selected_Room, selected_Time };
			}
		}
		else
		{
			printf("%d\n ", i);
		}



	}



};

void Chromosome::CalculateFitness()
{
	for (int time = 0; time < SUM_OF_TIME; time++)
		goodOfEveryTime[time] = badOfEveryTime[time] = 0;
	fitness = 0;


	for (int time = 0; time < SUM_OF_TIME; time++)
	for (int room = 0; room < SUM_OF_ROOM; room++)
	{
		int teacher = lessonlist[room][time].teacher;
		if (teacher != -1)
		{
			int lesson = 0;
			for (; lesson < 3; lesson++)
			{
				int QuestionnaireNumber = Questionnaire[teacher][lesson] % (SUM_OF_TIME/2);
				int u_or_d = Questionnaire[teacher][lesson] / (SUM_OF_TIME / 2);

				if ((u_or_d == time / (SUM_OF_TIME / 2)) &&
					(QuestionnaireNumber == (time % (SUM_OF_TIME / 2)) % 5) &&
					 lesson == lessonlist[room][time].lesson)
				{
					fitness++;
					goodOfEveryTime[time]++;
					lesson = 5;
				}
			
			}
			if (lesson == 3)
			{
				fitness -= 100;
				badOfEveryTime[time]--;
			}
		}
	}

}

void Chromosome::Crossover(Chromosome & in)
{
	Random rand;
	vector<int> badList;
	vector<Lesson> inputList;
	int min = 100;
	int mean = 0;

	for (int time = 0; time < SUM_OF_TIME; time++)
	{

		if (in.badOfEveryTime[time] <0 )
			badList.push_back(time);
	}

	if (badList.size() != 0)
	{

		for (int index = 0; index < badList.size(); index++)
		for (int room = 0; room < SUM_OF_ROOM; room++)
		if (in.lessonlist[room][badList[index]].no != -1)
			inputList.push_back(in.lessonlist[room][badList[index]]);
	}
	else
	{
		printf("");
	}
		
	



	for (int inIndex = 0; inIndex < inputList.size(); inIndex++)
	{
		vector<int> selectable_Time;
		int selected_Time;

		//若該值有該中 保留之

		int QuestionnaireNumber = 
			Questionnaire[inputList[inIndex].teacher][inputList[inIndex].lesson] % (SUM_OF_TIME / 2);
		int u_or_d = Questionnaire[inputList[inIndex].teacher][inputList[inIndex].lesson] / (SUM_OF_TIME / 2);

		int time = location[inputList[inIndex].no].time;
		int room = location[inputList[inIndex].no].room;
		if ((u_or_d == time / (SUM_OF_TIME / 2)) &&
			(QuestionnaireNumber == (time % (SUM_OF_TIME / 2)) % 5) &&
			inputList[inIndex].lesson == lessonlist[room][time].lesson)
			continue;


		//移除舊有資料
		Location loca = location[inputList[inIndex].no];
		lessonlist[loca.room][loca.time] = { -1, -1, -1, -1 };

		for (int time = 0; time < SUM_OF_TIME; time++)
		{
			bool isOK = true;
			
			//篩選掉空間為零者
			int space = 0;
			for (int room = 0; room < SUM_OF_ROOM; room++)
			if (lessonlist[room][time].no == -1)space++;

			if (space == 0)isOK = false;

			//篩選掉有衝突者
			for (int room = 0; room <SUM_OF_ROOM; room++)
			{
				if ( lessonlist[room][time].no != -1)
				{
					Lesson &thisLesson = lessonlist[room][time];
					Lesson &inputLesson = inputList[inIndex];

					if ((thisLesson.teacher == inputLesson.teacher) ||(thisLesson.grade == inputLesson.grade))
						isOK = false;
				}
			}


			if (isOK)
				selectable_Time.push_back(time);
		}

		if (selectable_Time.size() == 0){
			//printf("selectable_Time.size error\n");
			continue;
		}

		selected_Time = selectable_Time[rand.Next(selectable_Time.size())];

		for (int in_room = 0; in_room < SUM_OF_ROOM; in_room++)
		for (int room = 0; room <SUM_OF_ROOM; room++)
		{
			Lesson &thisLesson = lessonlist[room][selected_Time];
			Lesson &inputLesson = in.lessonlist[in_room][selected_Time];
			if (inputLesson.no != -1 && thisLesson.no == -1)
			{
				//插入
				thisLesson = inputLesson;

				room = SUM_OF_ROOM;//內迴圈脫離
			}
		}
	}
}

void Chromosome::Crossover2(Chromosome & in)
{
	Lesson temp[SUM_OF_ROOM][SUM_OF_TIME];
	memcpy(temp, lessonlist, sizeof(lessonlist));

	//複製一半過去
	for (int time = 0; time < SUM_OF_TIME / 2; time++)
	for (int room = 0; room < SUM_OF_ROOM; room++)
			lessonlist[room][time] = in.lessonlist[room][time];

	for (int time = 0; time < SUM_OF_TIME / 2; time++)
	for (int room = 0; room < SUM_OF_ROOM; room++)
	{
	//	if ()
	}



}

void Chromosome::Mutation()
{
	vector<int> badList;
	for (int index = 0; index < SUM_OF_TIME; index++)
	{
		if (goodOfEveryTime[index] == 0)
			badList.push_back(index);
	}
	
	vector<int> badList2;
	for (int index = 0; index < SUM_OF_TIME; index++)
	{
		if (goodOfEveryTime[index] == 0)
			badList2.push_back(index);
	}
	Random rand;
	int a = badList[rand.Next(badList.size())];
	int b = badList2[rand.Next(badList2.size())];
	if (a!=b)
	for (int room = 0; room < SUM_OF_ROOM; room++)
		swap(lessonlist[room][a], lessonlist[room][b]);

}
