#pragma once
#include <ctime>
class admin
{

public:
	void main_menu();
	void admin_menu();
	void borrow_book();
	void deposit_book();
	void password();
	void pass();
	void print_msg();

	double calculateFine(time_t dueDate);
};

