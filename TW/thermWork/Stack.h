#pragma once
#include <iostream>
#include "Vector.h"

template <class T>
class Stack
{
private:
	int head;
	int curMaxSize;
	T* arr;

	void resize() {													//resizing dynamic array using memcpy
		if (this->head + 2 >= this->curMaxSize) {
			int newSize = this->curMaxSize * 2;
			T* newArr = new T[newSize];
			memcpy(newArr, arr, this->curMaxSize * sizeof(T));
			arr = newArr;
			curMaxSize = newSize;
		}
	};
public:
	Stack() {
		this->curMaxSize = 10;
		this->arr = new T[this->curMaxSize];
		this->head = -1;
	};

	bool isEmpty() {
		return head < 0;
	};

	void push(T elem) { 				//before pushing resize array if it need
		resize();
		arr[++head] = elem;
	};

	T pop() {
		if (!isEmpty()) {
			return arr[head--];
		}
		else {
			throw std::runtime_error("Empty stack");
		}
	}

	T top() {
		return arr[head];
	}
	
	int size() {
		return head + 1;
	}

	Vector<T> toArray() {							//add all elemtnts to vector 
		Vector<T> resVec = Vector<T>();
		for (int i = head; i >= 0; i--)
		{
			resVec.push_back(arr[i]);
		}
		return resVec;
	}
};

