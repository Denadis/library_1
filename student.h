#pragma once
#include<ctime>
class Student
{
	char Stud_name[25];					//nazwa studenta
	int b_no;						//numer identyfikacyjny ksiazki przypisywany do studenta w momencie wypozyczania ksiazki
	int token;					//sluzy do sprawdzenia czy student ma wypozyczona jak¹œ ksi¹¿ke czy nie
	
public:
	Student();
	~Student();
	int Stud_ID;
	time_t borrowedAt;
	//Getters
	char* getStud_name();
	int getb_no();
	int get_token();
	//Setters
	void setStud_name(char* s_n);
	void set_token(int x);

	void reset_token();
	void create_stud();
	void show_stud();
	void show_list();
	bool res_student(int x);
	


};

