#pragma once
#include <iostream>

class Array {
	int m_size;
	int m_capacity;
	int* m_data;

	void Copy(const Array& obj);
public:
	Array();
	Array(int* newData, int newSize);
	Array(const Array& obj);
	~Array();

	Array& operator=(const Array& obj);

	int& size();
	int* data();
	int& operator[](int index);

	void push_back(int number);

	void Clear();

	friend std::ostream& operator<<(std::ostream& stream, const Array& arr);
};