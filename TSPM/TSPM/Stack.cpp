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
	//Creates a temporary array of the new size to copy stack to
	Project * temp = new Project[size + 1];
	//Copies stack data to temp array
	for (int i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}

	//Adds new element to the top of the stack
	temp[size] = p;

	//Sets stack data to updated stack
	data = temp;
	
	//Updates size of the stack
	size++;
}

Project Stack::pop()
{
	//Reduces the size of the stack
	//When a new element is pushed the element that used to be at the top of the stack will be overwritten
	size--;

	return data[size];
}

int Stack::getSize()
{
	//Returns the number of elements on the stack
	return size;
}

bool Stack::isEmpty()
{
	//Returns true if the stack is empty
	return size == 0;
}
