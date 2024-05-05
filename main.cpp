#include <iostream>
#include <math.h>

#include <fstream> //для удобного ввода массива из файла
#include <string> //также для удобного ввода массива
//Напишите программу для поиска k-го наименьшего элемента в массиве с помощью алгоритмов МИНК и МИНСК.
//Определите, какой из алгоритмов оказывается эффективнее для различных длин массива и различных k.

#include "array.h"

int calculateSizeArray()
{
	std::ifstream file("input.txt");
	if (!file.is_open())
	{
		std::cout << "Error open file\n";
		exit(EXIT_FAILURE);
	}

	std::string str;
	std::getline(file, str);

	if (str.size() == 0)
	{
		std::cout << "Error! You enter empty system!";
		exit(EXIT_FAILURE);
	}

	int size = 1;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
			size++;
	}

	//if (size == 0)
	//{
	//	std::cout << "Error! System size is 0!";
	//	exit(EXIT_FAILURE);
	//}

	file.close();

	return size;

}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void bubbleSort(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		bool flag_swapped = false;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				flag_swapped = true;
			}
		}
		if (!flag_swapped)
			break;
	}
}

int MINK(Array& array, int k)
{
	//Step 1. Разбиваем массив на пятерки

	int countOfNumbers = array.size();
	int parts = 5;
	int countOfArrays = ceil(countOfNumbers / parts);
	if (countOfNumbers % parts != 0)
		countOfArrays++;
	Array* listOfArrays = new Array[countOfArrays];
	int index = 0;
	for (int i = 0; i < countOfArrays; i++)
	{
		int sizeArr = 0;
		if (countOfNumbers > parts)
		{
			sizeArr = parts;
			countOfNumbers -= parts;
		}
		else
			sizeArr = countOfNumbers;


		int* data = new int[sizeArr];
		for (int j = 0; j < sizeArr; j++)
		{
			data[j] = array[index];
			index++;
		}

		//Step 2. Упорядочиваем пятерку
		bubbleSort(data, sizeArr);
		listOfArrays[i] = Array(data, sizeArr);
		std::cout << listOfArrays[i] << std::endl;
	}

	countOfNumbers = array.size();

	//Step 3. Формируем множество медиан
	Array median_arr;
	int median_index = parts / 2;
	for (int i = 0; i < countOfArrays; i++)
	{
		if (listOfArrays[i].size() > median_index)
		{
			median_arr.push_back(listOfArrays[i][median_index]);
		}
	}

	//std::cout << "DEBUG: median_arr = " << median_arr;

	//Step 4. Ищем медиану M. m = MINK(M, n/10)
	int median_true = MINK(median_arr, countOfNumbers / (parts*2) ); //parts = 5; 5*2=10. math!

	std::cout << "DEBUG: median_true = " << median_true;

	//Step 5. Формируем множества АМ, АР и АБ:
	Array numbers_less;
	Array numbers_equal;
	Array numbers_larger;

	for (int i = 0; i < countOfNumbers; i++)
	{
		if (array[i] < median_true)
			numbers_less.push_back(array[i]);
		else if (array[i] == median_true)
			numbers_equal.push_back(array[i]);
		else
			numbers_larger.push_back(array[i]);
	}

	//Step 6. Проверка условий и выполнение нужного действия
	if (k <= numbers_less.size())
		return MINK(numbers_less, k);
	else if (k > numbers_less.size() && k <= (numbers_less.size() + numbers_equal.size()))
		return median_true;
	else if (k > (numbers_less.size() + numbers_equal.size()))
		return MINK(numbers_larger, k - numbers_less.size() - numbers_equal.size());

	//for (int i = 0; i < countOfArrays; i++)
	//	delete[] listOfArrays[i].data();
	//delete[] listOfArrays;

	return 0;
}

int MINSK(Array& array, int k)
{
	return 0;
}

int main()
{
	int newSize = calculateSizeArray();
	int* arr = new int[newSize];

	std::ifstream file("input.txt");
	if (!file.is_open())
	{
		std::cout << "Error open file\n";
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < newSize; i++)
		file >> arr[i];

	file.close();

	Array array(arr, newSize);

	int k_num = 0;

	std::cout << "Enter positive k: ";
	std::cin >> k_num;
	std::cout << std::endl;
	while (k_num < 0)
	{
		std::cout << "Entered k < 0! Please, enter positive k: ";
		std::cin >> k_num;
		std::cout << std::endl;
	}

	int mink = MINK(array, k_num);

	std::cout << "Result MINK = " << mink;
	
	//std::cout << array << std::endl;

	//bubbleSort(array.data(), array.size());

	//std::cout << "Sorted: " << array << std::endl;

	delete[] arr;
	return 0;
}