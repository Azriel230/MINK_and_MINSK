#include "array.h"

Array::Array()
{
	m_size = 0;
	m_capacity = 0;
	m_data = nullptr;
}

Array::Array(int* newData, int newSize)
{
	if (newSize <= 0)
	{
		std::cout << "Error! Size of new array is <= 0!";
		exit(EXIT_FAILURE);
	}

	m_size = newSize;
	m_capacity = m_size * 2;
	m_data = new int[m_capacity];
	for (int i = 0; i < m_size; i++)
		m_data[i] = newData[i];
}

Array::Array(const Array& obj)
{
	Copy(obj);
}

void Array::Copy(const Array& obj)
{
	if (obj.m_size == 0 || obj.m_data == nullptr)
	{
		m_size = 0;
		m_capacity = 0;
		m_data = nullptr;
		return;
	}

	m_size = obj.m_size;
	m_capacity = obj.m_capacity;
	m_data = new int[m_capacity];

	for (int i = 0; i < m_size; i++)
		m_data[i] = obj.m_data[i];
}

void Array::Clear()
{
	if (m_data != nullptr)
	{
		m_size = 0;
		m_capacity = 0;
		delete[] m_data;
		m_data = nullptr;
	}
}

Array& Array::operator=(const Array& obj)
{
	if (this == &obj)
		return *this;

	Clear();
	Copy(obj);

	return *this;
}

Array::~Array()
{
	m_size = 0;
	m_capacity = 0;
	delete[] m_data;
}

int& Array::size()
{
	return m_size;
}

int* Array::data()
{
	return m_data;
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

std::ostream& operator<<(std::ostream& stream, const Array& arr)
{
	stream << '[';
	if (arr.m_size > 0)
	{
		for (int i = 0; i < arr.m_size - 1; i++)
			std::cout << arr.m_data[i] << " ";
		std::cout << arr.m_data[arr.m_size - 1];
	}
	stream << ']';
	return stream;
}

void Array::push_back(int number)
{
	if (m_size == m_capacity)
	{
		if (m_capacity == 0)
			m_capacity = 1;
		else
			m_capacity = m_size * 2;

		int* newArray = new int[m_capacity];
		for (int i = 0; i < m_size; i++)
			newArray[i] = m_data[i];

		delete[] m_data;

		m_data = newArray;
	}

	m_data[m_size] = number;
	m_size = m_size + 1;

	//m_data = new int[m_size + 1];
	//for (int i = 0; i < m_size; i++)
	//	m_data[i] = newArray[i];

	//delete[] newArray;
}