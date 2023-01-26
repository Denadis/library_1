#include "admin.h"
#include "librarian.h"
#include "student.h"
#include "book.h"
#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
using namespace std;

Student st1; Book bk1;

void admin::main_menu()
{
	int i;
	system("cls");
	system("COLOR 0B");
	cout << "\n***********************************************************************************************************************\n";
	cout << setw(40) <<" " << "WELCOME TO LIBRARY MANAGEMENT SYSTEM \n";
	cout << setw(50) << " " <<"MAIN MENU\n";
	cout << "\n***********************************************************************************************************************\n\n";
	cout << "\n\t\t\t>>Please Choose Any Option: \n\n";
	cout << "\n\t\t1. Borrow Book\n\n\t\t2. Deposit Book \n\n\t\t3. Administrator\n\n\t\t0. Exit";
	cout << "\n\n\t\tEnter your choice : ";
	cin >> i;
	if (i == 1)
	{
		borrow_book();
		system("cls");
		main_menu();
	}
	if (i == 2)
	{
		deposit_book();
		system("cls");
		main_menu();
	}
	if (i == 3)
	{
		pass();

	}
	if (i == 0)
	{
		exit(1);
	}
	else
	{
		cout << "\n\t\tWrong input: You need to write numbers beetween 1-3 or 0 to exit!!!";
		_getch();
		system("cls");
		main_menu();
	}
}
void admin::admin_menu()
{
	system("cls");
	system("COLOR 0C");
	cout << "\n***********************************************************************************************************************\n";
	cout << setw(45) << " " << "LIBRARY MANAGEMENT SYSTEM\n";
	cout << setw(50) << " " << "ADMIN MENU PAGE\n";
	cout << "\n***********************************************************************************************************************\n\n";
	cout << "\n\t\t\t\t>>Please Choose One Option:\n\n";
	cout << "\n\t\t\t1.Book Menu\n\n\t\t\t2.Student Menu \n\n\t\t\t3.Go to main menu\n\n\t\t\t4.Change Password\n\n\t\t\t5.Close Application\n";
	cout << "\n\t\t\tEnter your choice : ";
	int i;
	cin >> i;
	if (i == 1)
	{
		system("cls");
		librarian().book_menu();
	}
	if (i == 2)
	{
		librarian().student_menu();
	}
	if (i == 3)
	{	
		system("cls");
		main_menu();
	}
	if (i == 4)
	{
		system("cls");
		print_msg();
		password();
	}
	if (i == 0)
	{
		exit(0);
	}
	else
	{
		cout << "\n\t\tWrong input: You need to write numbers beetween 1-4 or 0 to exit!!!";
		_getch();
		system("cls");
		admin_menu();
	}
}
double admin::calculateFine(time_t dueDate) {
	if (dueDate >= st1.borrowedAt) { // sprawdzenie, czy data zwrotu jest po terminie
		double fine = difftime(dueDate, st1.borrowedAt) * 2; // obliczenie kary
		return fine;
	}
	return 0;
}
void admin::borrow_book()  //funkcja do wypo¿yczania ksi¹¿ki 
{
	int s_id, b_id;
	system("CLS");
	print_msg();
	cout << "\n\n\t\t*****Borrow Book******";
	cout << "\n\n\t\tEnter the student's ID: ";
	cin >> s_id;
	int cnt = 0;
	fstream outf("student.bin", ios::in | ios::out | ios::ate | ios::binary);
	outf.seekg(0, ios::beg);
	if (!outf)
		cout << "\n\t\tFile not found\n";
	else
	{
		while (outf.read((char*)&st1, sizeof(Student)))
		{
			if (st1.Stud_ID == s_id)
			{
				if (st1.getb_no()) {
					cout << "\n\t\t You didn't return your last book!";
					_getch();
					system("cls");
					main_menu();
				}	
				cnt++;
				system("cls");
				print_msg();
				st1.show_stud();
				librarian().list_book();
				cout << "\n\t\tChoose which book you want to borrow from the list above!(write 0 to cancel)";
				cout << "\n\n\t\tEnter the book ID: ";
				cin >> b_id;
				if (b_id == 0)
					main_menu();
				cout << "\n";
				system("cls");
				print_msg();
				int flag = Book().res_book(b_id, 1);
				if (flag == 1)
				{
					st1.set_token(b_id);
					st1.borrowedAt = time(nullptr);
					int pos;
					pos = outf.tellp();
					outf.seekp(pos - sizeof(Student));
					outf.write((char*)&st1, sizeof(Student));
					cout << "\n\t\tBook Borrowed by " << st1.getStud_name() << endl;
					cout << "\n\n\t\tNote: ";
					cout << "\n\t\t      Should be submitted within 15 days to avoid fine";
					cout << "\n\t\t      The fine is 2$ for each day after 15 days period\n";
					break;
				}
				else if (flag == 2)
				{
					cout << "\n\t\tTHE BOOK IS OUT OF STOCK!!!";
					break;
				}
				else
				{
					cout << "\n\t\tNo book of given ID\n";
					break;
				}
			}
		}
		if (cnt == 0)
			cout << "\n\t\tStudent of given ID doesn't exist\n";
	}
	outf.close();
	cout << "\n\n\t\tPress any key to continue...";
	_getch();
}
void admin::deposit_book()
{
	
	system("CLS");
	print_msg();
	cout << "\n\n\t\t*****BOOK DEPOSIT******";
	cout << "\n\n\t\tEnter the student's ID: ";
	int s_id, b_id;
	cin >> s_id;
	int cnt = 0;
	fstream outf("student.bin", ios::in | ios::out | ios::ate | ios::binary);
	outf.seekg(0, ios::beg);
	if (!outf)
		cout << "\n\t\tFile not found\n";
	else
	{
		while (outf.read((char*)&st1, sizeof(Student)))
		{
			if (st1.Stud_ID == s_id)
			{
				cnt++;
				b_id = st1.getb_no();
				bool flag = Book().res_book(b_id, 2);
				if (flag)
				{
					time_t dueDate = st1.borrowedAt + (7);		//na potrzeby programu dopisa³em  7 dni po terminie
					double fine = calculateFine(dueDate);
					if (fine > 0) {
						cout << "\n\n\t\tStudent " << st1.getStud_name() << " need to pay fine  " << fine << "$ for not returning book in time";
						cout << "\n\n\t\tRemember:\n\n\t\t   You need to pay a fine before you can borrow another book!";
					}
					st1.reset_token();
					int pos;
					pos = outf.tellp();
					outf.seekp(pos - sizeof(Student));
					outf.write((char*)&st1, sizeof(Student));
					cout << "\n\n\t\tBook Deposited Successfully\n";
					break;
				}
				else
				{
					cout << "\n\t\tStudent of given ID doesn't have any borrowed book\n";
					break;
				}
			}
		}
		if (cnt == 0)
			cout << "\n\t\tStudent of given ID doesn't exist\n";
	}
	outf.close();
	cout << "\n\n\t\tPress any key to continue...";
	_getch();
}
void admin::pass()
{
	system("cls");
	print_msg();
	int i = 0;
	char ch, st[21], ch1[21] = { "pass" };
	cout << "\n\t\tEnter Password : ";
	while (1)
	{
		ch = _getch();
		if (ch == 13)
		{
			st[i] = '\0';
			break;
		}
		else if (ch == 8 && i > 0)
		{
			i--;
			cout << "\b \b";
		}
		else
		{
			cout << "*";
			st[i] = ch;
			i++;
		}
	}
	ifstream inf("password.txt");
	inf >> ch1;
	inf.close();
	for (i = 0; st[i] == ch1[i] && st[i] != '\0' && ch1[i] != '\0'; i++);
	if (st[i] == '\0' && ch1[i] == '\0')
	{
		cout << "\n\n\t\t Login succesful!";
		cout << "\n\n\t\tPress any key to continue......";
		_getch();
		admin_menu();
	}
	else
	{
		cout << "\n\n\t\tWrong Password.\n\n";
		cout << "\n\t\tEnter 1 for retry or 2 for menu";
		cin >> i;
		if (i == 1)
		{
			system("cls");
			print_msg();
			pass();
		}
		else
		{
			system("cls");
			main_menu();
		}
	}
}
void admin::password()
{
	system("cls");
	print_msg();
	int i = 0, j = 0;
	char ch, st[21], ch1[21] = { "pass" };
	cout << "\n\n\t\tEnter Old Password : ";
	while (1)
	{
		ch = _getch();
		if (ch == 13)
		{
			st[i] = '\0';
			break;
		}
		else if (ch == 8 && i > 0)
		{
			i--;
			cout << "\b \b";
		}
		else
		{
			cout << "*";
			st[i] = ch;
			i++;
		}
	}
	ifstream intf("password.txt");
	intf >> ch1;
	intf.close();
	for (i = 0; st[i] == ch1[i] && st[i] != '\0' && ch1[i] != '\0'; i++);
	if (st[i] == '\0' && ch1[i] == '\0')
	{
		system("cls");
		print_msg();
		cout << "\n\t**The Password Should be less than 20 characters & don't use spaces**\n\n";
		cout << "\n\t\tEnter New Password : ";
		fflush(stdin);
		i = 0;
		while (1)
		{
			j++;
			ch = _getch();
			if (ch == 13)
			{
				for (i = 0; st[i] != ' ' && st[i] != '\0'; i++);
				if (j > 20 || st[i] == ' ')
				{
					cout << "\n\n\t\tYou did't follow the instruction \n\n\t\tPress any key for try again.....";
					_getch();
					system("cls");
					password();
					admin_menu();
				}
				st[i] = '\0';
				break;
			}
			else if (ch == 8 && i > 0)
			{
				i--;
				cout << "\b \b";
			}
			else
			{
				cout << "*";
				st[i] = ch;
				i++;
			}
		}
		ofstream outf("password.txt");
		outf << st;
		outf.close();
		cout << "\n\n\t\tYour Password has been changed Successfully.";
		cout << "\n\n\t\tPress any key to continue......";
		_getch();
		system("cls");
		admin_menu();
	}
	else
	{
		cout << "\n\n\t\tPassword is incorrect.....\n";
		cout << "\n\t\tEnter 1 for retry or 2 for menu";
		cin >> i;
		if (i == 1)
		{
			system("cls");
			print_msg();
			password();
		}
		else
		{
			system("cls");
			admin_menu();
		}
	}
}
void admin::print_msg()
{
	system("cls");
	system("COLOR 03");
	cout << "\n***********************************************************************************************************************\n";
	cout << setw(45)<<" "<< "LIBRARY MANAGEMENT SYSTEM\n";
	cout << "\n***********************************************************************************************************************\n";
}
