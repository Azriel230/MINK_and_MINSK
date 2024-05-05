#include "array.h"

Array::Array() 
{
	m_size = 0;
	m_data = nullptr;
}

Array::Array(int newSize, int* newData)
{
	if (newSize <= 0)
	{
		std::cout << "Error! Size of new array is <= 0!";
		exit(EXIT_FAILURE);
	}

	m_size = newSize;
	m_data = new int[newSize];
	for (int i = 0; i < newSize; i++)
		m_data[i] = newData[i];
}

Array::~Array()
{
	m_size = 0;
	delete[] m_data;
}

int& Array::size()
{
	return m_size;
}

int& Array::operator[](int& index)
{
	if (index < 0 || index > m_size)
	{
		std::cout << "Error! Out of rande array!";
		exit(EXIT_FAILURE);
	}

	return m_data[index];
}

std::ostream& operator<<(std::ostream& stream,const Array& arr)
{
	stream << '[';
	if (arr.m_size > 0)
	{
		for (int i = 0; i < arr.m_size - 1; i++)
			std::cout << arr.m_data[i] << " ";
	}
	std::cout << arr.m_data[arr.m_size - 1];
	stream << ']';
	return stream;
}

void Array::push_back(int& number)
{
	int* newArray = new int[m_size + 1];
	for (int i = 0; i < m_size; i++)
		newArray[i] = m_data[i];
	newArray[m_size] = number;

	delete[] m_data;

	m_data = newArray;

	//m_data = new int[m_size + 1];
	//for (int i = 0; i < m_size; i++)
	//	m_data[i] = newArray[i];

	//delete[] newArray;
}
