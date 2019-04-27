#pragma once

#include "Project.h"

class Stack
{
public:
	Stack();
	~Stack();


	void push(Project p);

	Project pop();

	int getSize();

	bool isEmpty();

private:
	Project * data;

	int size = 0;

};

