#include "book.h"
#include <iostream>
#include <fstream>
#include<iomanip>

using namespace std;

Book::Book()
{
}
Book::~Book()
{
}
int Book::getID()
{
	return Book_ID;
}
void Book::setTitle(char* n)
{
	strcpy_s(Title, n);
}
char* Book::getTitle()
{
	return Title;
}
void Book::setAuthor(char* a)
{
	strcpy_s(Author, a);
}
char* Book::getAuthor()
{
	return Author;
}
int Book::getQ() 
{
	return Q;
}
void Book::setQ()
{
	Q -= 1;
}
void Book::reset_Q()
{
	Q += 1;
}
void Book::assign_id(int x)   // funkcja przypisuje numer identyfikacyjny dla ksi¹¿ki 
{
	Book_ID = 10001;
	Book_ID += x - 1;
start1:
	Book_ID += 1;
	if (res_book(Book_ID, 0))
		goto start1;
}

void Book::create_book()						//Funkcja do tworzenia nowych ksiazek
{
	int i;
	cout << "\n\t\t Enter the details of the book! \n";
	cout << "\n\n\t\tEnter Book's title: ";
	char n[50];
	cin.getline(n, 50);
	cin.getline(Title, 50);
	for (i = 0; Title[i] != '\0'; i++)
	{
		if (Title[i] >= 'a' && Title[i] <= 'z')
			Title[i] -= 32;   //przesuwaj¹c o 32 miejsca w kodzie ASCII zapisujemy ma³¹ litere jako  du¿¹
	}
	cout << "\n\t\tEnter Author's Name: ";
	cin.getline(Author, 50);
	cout << "\n\t\tEnter Book's quantity: ";
	cin >> Q;
}

void Book::show_book()							//Funkcja do wyœwietlania dok³adnie jednej ksiazki
{
	cout << "\n\t\tBook ID: " << Book_ID << endl;
	cout << "\n\t\tBook Name: " << Title << endl;
	cout << "\n\t\tBook's Author Name: " << Author << endl;
	if (Q >= 1)								//wyœwietla siê tylko gdy iloœæ ksi¹zek jest wieksza b¹dŸ równa 1
	{
		cout << "\n\t\tBook's Quantity: " << Q << endl;;
	}
	
}

void Book::show_books()						//Forma wyswietlania listy ksiazek
{
	cout << "\n\t"<<setw(24) << left << Book_ID << setw(33) << Title << setw(38) << Author << setw(10) << Q << endl;
}

int Book::res_book(int x, int z)   //funkcja do resetowania/ ustawiania iloœci ksi¹¿ek. Parametr x s³u¿y do wyszukiwania ksiazki po id, natomiast parametr z zale¿y od funkcji.
								  //Dla funkcji do wypo¿yczania ksi¹¿ki przyjmuje parametr 1, dla funkcji zwracania ksi¹¿ki 2
								// Zwraca parametr flag (2 oznacza ze ilosc sztuk danej ksiazki wynosi 0, 1 ze jest dostepna, 0 ze nie ma takiej ksiazki
{
	int count = 0, flag = 1;
	Book b;
	fstream intf("book1.bin", ios::in | ios::out | ios::ate | ios::binary);
	intf.seekg(0, ios::beg);
	if (!intf)
		flag = 0;
	else
	{
		while (intf.read((char*)&b, sizeof(Book)))
		{
			if (b.getID() == x)
			{
				count++;
				if (z == 1)
				{

					b.show_book();
					if (b.getQ() > 0)
					{
						b.setQ();   
						int pos;
						pos = intf.tellp();    ///tellp zwraca pozycje wskaŸnika w pliku
						intf.seekp(pos - sizeof(Book));   ///seekp ustawia pozycje wskaŸnika zapisywania danych 
						intf.write((char*)&b, sizeof(Book));  ///zapisuje dane w pliku
					}
					else
						flag = 2;
				}
				else if (z == 2)
				{
					b.show_book();
					b.reset_Q();
					int pos;
					pos = intf.tellp();
					intf.seekp(pos - sizeof(Book));
					intf.write((char*)&b, sizeof(Book));
				}
				break;
			}
		}
		if (count == 0)
			flag = 0;
	}
	intf.close();
	return flag;
}