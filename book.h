#pragma once
class Book
{
	char Title[50];
	char Author[50];
	int Q; //iloœæ sztuk 
protected:
	int Book_ID;

public:

	Book();
	~Book();

	//Getters
	int getID();
	char* getTitle();
	char* getAuthor();
	int getQ();

	void setTitle(char* n);
	void setAuthor(char* a);
	void setQ();

	void reset_Q();
	void assign_id(int x);
	void create_book();
	void show_book();
	void show_books();
	int res_book(int x, int z);
	
};

