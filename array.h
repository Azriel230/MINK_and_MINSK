#include <iostream>

class Array {
	int m_size;
	int* m_data;

public:
	Array();
	Array(int newSize, int* newData);
	~Array();
	
	int& size();
	int& operator[](int& index);

	void push_back(int& number);

	friend std::ostream& operator<<(std::ostream& stream, const Array& arr);
};