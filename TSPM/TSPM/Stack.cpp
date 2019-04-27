#include "stdafx.h"
#include "Stack.h"

Stack::Stack()
{
}


Stack::~Stack()
{
}

void Stack::push(Project p)
{
	
	Project * temp = new Project[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	temp[size] = p;

	data = temp;
	

	size++;
}

Project Stack::pop()
{
	size--;

	return data[size];
}

int Stack::getSize()
{
	return size;
}

bool Stack::isEmpty()
{
	return size == 0;
}
