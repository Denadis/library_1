#include "student.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>

using namespace std;


Student::Student()
{

}
Student::~Student()
{

}
char* Student::getStud_name()
{
    return Stud_name;
}

void Student::setStud_name(char* s_n)
{
    strcpy_s(Stud_name, s_n);
}

int Student::getb_no()
{
    return b_no;
}
int Student::get_token()
{
    return token;
}

void Student::set_token(int x)  // funkcja do przypisywania numeru id ksiazki do studenta. Parametr x oznacz Book_ID, ustawia token = 1 co oznacza ze student ma wypozyczona ksi¹¿kê
{
    b_no = x;
    token = 1;
}
void Student::reset_token() //resetuje id wypozyczonej ksiazki, date wypozyczenia i token 
{
    b_no = 0;
	borrowedAt = 0;
    token = 0;
}


void Student::create_stud()				// Tworzenie nowego studenta w bazie
{
    int i;
	cout << "\n\t\tEnter the details:-\n";
	cout << "\n\t\tEnter student's ID: ";
	cin >> Stud_ID;
	if (res_student(Stud_ID))
	{
		cout << "\n\t\tStudent of given ID already exist";
		cout << "\n\n\t\tEnter a different ID!\n";
		_getch();
		system("cls");
		create_stud();
	}

	cout << "\n\t\tEnter student's Name: ";
	char n[50];
	cin.getline(n, 50);
	cin.getline(Stud_name, 25);
	for (i = 0; Stud_name[i] != '\0'; i++)
	{
		if (Stud_name[i] >= 'a' && Stud_name[i] <= 'z')
			Stud_name[i] -= 32;    //przesuwaj¹c o 32 miejsca w kodzie ASCII zapisujemy ma³¹ litere jako  du¿¹
	}
	b_no = 0;
	borrowedAt = 0;
	token = 0;
}


void Student::show_stud()                                     //Wyœwietla informacje o studencie															/
{															  //jesli token jest równy 1 to tak¿e wyœwietla ID wypo¿yczonej ksi¹¿ki
	cout << "\n\t\tStudent's ID: " << Stud_ID << endl;				
	cout << "\n\t\tStudent's Name: " << Stud_name << endl;
	if (token == 1)  
	{
		cout << "\n\t\tBorrowed Book (Book ID): " << b_no;
	}
}


void Student::show_list()                                  // Funkcja do wyœwietlenia listy studentów
{
	cout << "\n"<< setw(16) << left << " " << setw(26)  << Stud_ID << setw(36) << Stud_name << setw(38) << b_no << endl;

}
bool Student::res_student(int x)   // funkcja s³u¿y do sprawdzania czy student o podanym id ju¿ istnieje, zwraca 1 gdy istnieje, 0 gdy nie
{
	int cnt = 0, f = 0;
	Student s;
	ifstream intf("student.bin", ios::in | ios::binary);
	intf.seekg(0, ios::beg);
	if (!intf)
		f = 1;
	else
	{
		while (intf.read((char*)&s, sizeof(Student)))
		{
			if (s.Stud_ID == x)
			{
				cnt++;
				break;
			}
		}
		if (cnt == 0)
			f = 1;
	}
	intf.close();
	if (f)
		return 0;
	else
		return 1;
}

