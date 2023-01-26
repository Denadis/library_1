#include "librarian.h"
#include "book.h"
#include "student.h"
#include "admin.h"
#include<iostream>
#include<fstream>
#include <conio.h>
#include<iomanip>

using namespace std;
Book bk;

librarian::librarian()
{

}
librarian::~librarian()
{

}
void librarian::book_menu()
{
	system("cls");
	system("COLOR 09");
	cout << "\n***********************************************************************************************************************\n";
	cout << setw(45) << " " << "LIBRARY MANAGEMENT SYSTEM\n";
	cout << setw(50) << " " << "BOOK MENU PAGE\n";
	cout << "\n***********************************************************************************************************************\n\n";
	cout << "\n\t\t\t>>Please Choose One Option: \n";
	cout << "\n\n\t\t\t1. Add New Book";
	cout << "\n\n\t\t\t2. Display All Books";
	cout << "\n\n\t\t\t3. Search Specific Book";
	cout << "\n\n\t\t\t4. Modify Book Data ";
	cout << "\n\n\t\t\t5. Remove Book";
	cout << "\n\n\t\t\t0. Back to admin menu";
	cout << "\n\n\t\t\t   Enter your choice: ";
	int i = 0;
	cin >> i;
	if (i == 1)
	{
		system("cls");
		admin().print_msg();
		write_book();
		cout << endl;
		book_menu();
	}
	else if (i == 2)
	{
		system("cls");
		admin().print_msg();
		list_book();
		cout << "\n\n\t\tPress any key to continue...";
		_getch();
		cout << endl;
		book_menu();
	}
	else if (i == 3)
	{
		system("CLS");
		admin().print_msg();
		search_book();
		cout << endl;
		book_menu();
	}
	else if (i == 4)
	{
		system("CLS");
		admin().print_msg();
		modify_book();
		cout << endl;
		book_menu();
	}
	else if (i == 5)
	{
		system("CLS");
		admin().print_msg();
		delete_book();
		cout << endl;
		book_menu();
	}
	else if (i == 0)
	{
		admin().admin_menu();
	}
	else
	{
		cout << "\n\t\tWrong input: You need to write numbers beetween 1-5 or 0 to return to previous menu!!!";
		_getch();
		system("cls");
		book_menu();
	}

}
void librarian::write_book()
{
	ofstream outf("book1.bin", ios::app | ios::binary);
	outf.seekp(0, ios::end);  ///ustawia pozycje wskaznika zapisywania danych na koniec pliku
	int x = outf.tellp() / sizeof(Book);  ///tellp zwraca pozycje wskaünika w pliku
	bk.assign_id(x);
	bk.create_book();
	bk.show_book();
	outf.write((char*)&bk, sizeof(Book));
	cout << "\n\t\tRecord added successfully";
	outf.close();
	_getch();
}
void librarian::list_book()
{
	ifstream intf("book1.bin", ios::in | ios::binary);
	intf.seekg(0, ios::beg);
	if (!intf)
		cout << "\n\t\tFile not found\n";
	else
	{
		cout << "========================================================================================================================\n";
		cout << "- - - - BOOK ID - - - - " <<  "- - - - NAME OF THE BOOK - - - - " << "- - - - NAME OF THE AUTHOR - - - - "<<"- - - - QUANTITY - - - -\n";
		cout << "========================================================================================================================\n";
		while (intf.read((char*)&bk, sizeof(Book)))
		{
			bk.show_books();
		}
	}
	intf.close();
}
void librarian::search_book()
{
	int count = 0;
	ifstream intf("book1.bin", ios::in | ios::binary);
	intf.seekg(0, ios::beg);   ///  przesuwa wskaünik na poczπtek pliku
	if (!intf)
		cout << "\n\t\tFile not found";
	else
	{
		cout << "\n\n\n\t\tEnter the ID of the book you looking for(write 0 to cancel): ";
		int id;
		cin >> id;
		if (id == 0)
			librarian().book_menu();
		while (intf.read((char*)&bk, sizeof(Book)))
		{
			if (bk.getID() == id)
			{
				count++;
				cout << "\n\t\tBook Found!!!\n\n";
				bk.show_book();
				break;
			}
		}
		if (count == 0)
			cout << "\n\t\tNo such record exists";
	}
	intf.close();
	cout << "\n\n\t\tPress any key to continue...";
	_getch();
}
void librarian::modify_book()
{
	int cnt = 0;
	fstream intf("book1.bin", ios::in | ios::out | ios::ate | ios::binary);
	intf.seekg(0, ios::beg);
	if (!intf)
		cout << "\n\t\tFile not found\n";
	else
	{
		list_book();
		cout << "\n\n\n\t\tEnter the ID of the book you want to edit(write 0 to cancel): ";
		int id;
		cin >> id;
		if (id == 0)
			librarian().book_menu();
		while (intf.read((char*)&bk, sizeof(Book)))
		{
			if (bk.getID() == id)
			{
				cnt++;
				system("cls");
				bk.create_book();
				bk.show_book();
				int pos;
				pos = intf.tellp();    ///zwraca pozycje 
				intf.seekp(pos - sizeof(Book));   ///seekp ustawia pozycje wskaünika zapisywania danych 
				intf.write((char*)&bk, sizeof(Book));   
				cout << "\n\t\tRecord Updated";
				break;
			}
		}
		if (cnt == 0)
			cout << "\n\t\tRecord of given ID  doesn't exists";
	}
	intf.close();
	_getch();
}
void librarian::delete_book()
{
	int cnt = 0;
	fstream intf("book1.bin", ios::in | ios::binary);
	intf.seekg(0, ios::beg);
	if (!intf)
		cout << "\n\t\tFile not found";
	else
	{
		librarian().list_book();
		cout << "\n\n\n\t\tEnter the ID of the book you want to remove(write 0 to cancel): ";
		int id;
		cin >> id;
		if (id == 0)
			librarian().book_menu();
		ofstream outf("temp.bin", ios::app | ios::binary);
		while (intf.read((char*)&bk, sizeof(Book)))
		{
			if (bk.getID() == id)
				cnt++;
			else
				outf.write((char*)&bk, sizeof(Book));
		}
		intf.close();
		outf.close();
		if (cnt == 0)
		{
			remove("temp.bin");
			cout << "\n\t\tBook of given ID doesn't exists";
		}
		else
		{
			remove("book1.bin");
			rename("temp.bin", "book1.bin");
			cout << "\n\t\tRecord deleted successfully";
		}
	}
	cout << "\n\n\t\tPress any key to continue...";
	_getch();
}


Student st;
void librarian::student_menu()
{
	system("cls");
	system("COLOR 0D");
	cout << "\n***********************************************************************************************************************\n";
	cout << setw(45) << " " <<"LIBRARY MANAGEMENT SYSTEM\n";
	cout << setw(50) << " " <<"STUDENT MENU PAGE\n";
	cout << "\n***********************************************************************************************************************\n\n";
	cout << "\n\t\t\t>>Please Choose One Option: \n";
	cout << "\n\n\t\t\t1. Create New Student ";
	cout << "\n\n\t\t\t2. Display All Students";
	cout << "\n\n\t\t\t3. Display Specific Student ";
	cout << "\n\n\t\t\t4. Modify Student Data ";
	cout << "\n\n\t\t\t5. Remove Student";
	cout << "\n\n\t\t\t0. Back to admin menu";
	cout << "\n\n\t\t\tEnter your choice: ";
	int i;
	cin >> i;
	if (i == 1)
	{
		system("cls");
		admin().print_msg();
		write_student();
		cout << endl;
		student_menu();
		
	}
	else if (i == 2)
	{
		system("cls");
		admin().print_msg();
		list_student();
		cout << endl;
		student_menu();
	}
	else if (i == 3)
	{
		system("cls");
		admin().print_msg();
		search_student();
		cout << endl;
		student_menu();
	}
	else if (i == 4)
	{
		system("cls");
		admin().print_msg();
		modify_student();
		cout << endl;
		student_menu();
	}
	else if (i == 5)
	{
		system("cls");
		cout << endl;
		admin().print_msg();
		delete_student();
		student_menu();
	}
	else if (i == 0)
	{
		admin().admin_menu();
	}
	else
	{
		cout << "\n\t\tWrong input: You need to write numbers beetween 1-5 or 0 to return to previous menu!!!";
		_getch();
		system("cls");
		book_menu();
	}
}

void librarian::write_student()
{
	ofstream outf("student.bin", ios::app | ios::binary);
	outf.seekp(0, ios::end);
	st.create_stud();
	st.show_stud();
	outf.write((char*)&st, sizeof(Student));
	cout << "\n\n\t\tStudent added!";
	outf.close();
	_getch();
}
void librarian::list_student()
{
	ifstream intf("student.bin", ios::in | ios::binary);
	intf.seekg(0, ios::beg);
	if (!intf)
		cout << "\n\t\tFile not found";
	else
	{
		cout << "========================================================================================================================\n";
		cout << "- - - - - - - - STUDENT ID - - - - " << "- - - - STUDENT NAME - - - - " << "- - - - BORROWED BOOK ID - - - - - - - - - - - - - -\n";
		cout << "========================================================================================================================\n";
		while (intf.read((char*)&st, sizeof(Student)))
			st.show_list();
	}
	intf.close();
	cout << "\n\n\n\t\t Press any key to continue...";
	_getch();
}
void librarian::search_student()
{
	int cnt = 0;
	ifstream intf("student.bin", ios::in | ios::binary);
	intf.seekg(0, ios::beg);
	if (!intf)
		cout << "\n\t\tFile not found";
	else
	{
		cout << "\n\n\n\t\tEnter the ID of the student: ";
		int id;
		cin >> id;
		if (id == 0)
			student_menu();
		while (intf.read((char*)&st, sizeof(Student)))
		{
			if (st.Stud_ID == id)
			{
				cnt++;
				cout << "\n\t\tStudent found!!!\n";
				st.show_stud();
				break;
			}
		}
		if (cnt == 0)
			cout << "\n\t\tStudent of given ID doesn't exists";
	}
	intf.close();
	cout << "\n\n\t\tPress any key to continue...";
	_getch();
}
void librarian::modify_student()
{
	int cnt = 0;
	fstream intf("student.bin", ios::in | ios::out | ios::ate | ios::binary);
	intf.seekg(0, ios::beg);
	if (!intf)
		cout << "\n\t\tFile not found";
	else
	{
		cout << "\n\n\n\t\tEnter the ID of the student(write 0 to cancel): ";
		int id;
		cin >> id;
		if (id == 0)
			student_menu();
		while (intf.read((char*)&st, sizeof(Student)))
		{
			if (st.Stud_ID == id)
			{
				cnt++;
				st.create_stud();
				st.show_stud();
				int pos;
				pos = intf.tellp();
				intf.seekp(pos - sizeof(Student));
				intf.write((char*)&st, sizeof(Student));
				cout << "\n\t\tRecord Updated";
				break;
			}
		}
		if (cnt == 0)
			cout << "\n\t\tStudent of given ID doesn't exists";
	}
	intf.close();
	cout << "\n\n\t\tPress any key to continue...";
	_getch();
}
void librarian::delete_student()
{
	int cnt = 0;
	ifstream intf("student.bin", ios::in | ios::binary);
	intf.seekg(0, ios::beg);
	if (!intf)
		cout << "\n\t\tFile not found";
	else
	{
		cout << "\n\n\n\t\tEnter the ID of the student: ";
		int id;
		cin >> id;
		if (id == 0)
			student_menu();
		ofstream outf("temp.bin", ios::app | ios::binary);
		while (intf.read((char*)&st, sizeof(Student)))
		{
			if (st.Stud_ID == id) {
				st.show_stud();
				if (st.getb_no() > 0) {
					cout << "\n\n\t\t You can't remove student who has borrowed book!!!";
					_getch();
					student_menu();
				}
				cnt++;
			}
			else
				outf.write((char*)&st, sizeof(Student));
		}
		intf.close();
		outf.close();
		if (cnt == 0)
		{
			remove("temp.bin");
			cout << "\n\t\tStudent of given ID doesn't exists";
		}
		else
		{
			remove("student.bin");
			rename("temp.bin", "student.bin");
			cout << "\n\t\tStudent removed successfully";
		}
	}
	cout << "\n\n\t\tPress any key to continue...";
	_getch();
}
