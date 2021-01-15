#pragma once
#include <iostream>

template <class T>
class Vector
{
private:
	int last;
	int size;
	T* arr;

	void resize() {											//resizing dynamic array using memcpy
		if (this->last + 2 >= this->size) {
			int newSize = this->size * 2;
			T* newArr = new T[newSize];
			memcpy(newArr, arr, this->size * sizeof(T));
			arr = newArr;
			size = newSize;
		}
	};
public:
	Vector() {
		this->size = 10;
		this->arr = new T[this->size];
		this->last = -1;
	};

	int length() {
		return this->last + 1;
	};

	bool isEmpty() {
		return last < 0;
	};

	void push_back(T elem) {
		resize();
		arr[++last] = elem;
	};

	T operator[](int i) {
		return arr[i];
	}
};

