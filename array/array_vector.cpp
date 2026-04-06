#include <algorithm>
#include <ostream>
#include <iostream>
#include "Header.h"

Array::Array(int startCapacity)
{
	if (startCapacity <= 0)
		capacity = DEFAULT_CAPACITY;
	else
		capacity = startCapacity;
	ptr = new int[capacity];
	size = 0;
}

Array::~Array()
{
	delete[] ptr;
}

Array::Array(const Array& arr)
{
	ptr = new int[arr.capacity];
	size = arr.size;
	capacity = arr.capacity;
	for (int i = 0; i < size; i++)
		ptr[i] = arr.ptr[i];
}

Array& Array::operator =(const Array& arr)
{
	if (this == &arr)
		return *this;
	if (capacity != arr.capacity)
	{
		delete[] ptr;
		ptr = new int[arr.capacity];
		capacity = arr.capacity;
	}
	size = arr.size;
	for (int i = 0; i < size; i++)
		ptr[i] = arr.ptr[i];
	return *this;
}

int& Array::operator [](int index)
{
	if (index >= size || index < 0)
		throw Exception();
	else
		return ptr[index];
}

void Array::insert(int elem, int index)
{
	if (index < 0 || index > size)
		throw Exception();
	if (size == capacity)
		increaseCapacity(size + 1);
	for (int j = size - 1; j >= index; j--)
		ptr[j + 1] = ptr[j];
	size++;
	ptr[index] = elem;
}

void Array::insert(int elem)
{
	insert(elem, size);
}

void Array::increaseCapacity(int newCapacity) {
	capacity = newCapacity < capacity * 2 ?
		capacity * 2 : newCapacity;
	int* newPtr = new int[capacity];
	for (int i = 0; i < size; i++)
		newPtr[i] = ptr[i];
	delete[] ptr;
	ptr = newPtr;
}

void Array::remove(int index)
{
	if (index < 0 || index >= size)
		throw Exception();
	for (int j = index; j < size - 1; j++)
		ptr[j] = ptr[j + 1];
	size--;
}

int Array::getSize() const
{
	return size;
}

std::ostream& operator <<(std::ostream& out, const Array& arr)
{
	out << "Total size: " << arr.size << std::endl;
	for (int i = 0; i < arr.size; i++)
		out << arr.ptr[i] << std::endl;
	return out;
}

void f(int k) {
	try
	{
		int res = g(k);
	}
	catch (Exception& e)
	{
		std::cout << "Произошла ошибка!!" << std::endl;
	}
}

int g(int n) {
	if (n)
		throw Exception();
	return n + 1;
}

template <class T> const T& getMax(
	const T& a, const T& b)
{
	return a > b ? a : b;
}