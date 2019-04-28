#pragma once

#include "Project.h"

template <class T>
class Stack
{
public:
	Stack() {}
	
	~Stack() {}


	void push(T p)
	{
		//Creates a temporary array of the new size to copy stack to
		T * temp = new T[size + 1];
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

	T pop()
	{
		//Reduces the size of the stack
		//When a new element is pushed the element that used to be at the top of the stack will be overwritten
		size--;

		return data[size];
	}

	int getSize()
	{
		return size;
	}

	bool isEmpty()
	{
		return size == 0;
	}

private:
	T * data;

	int size = 0;

};

