#include <iostream>
#include <math.h>
#include <time.h>
#include <ctime>

#include <fstream> //для удобного ввода массива из файла
#include <string> //также для удобного ввода массива
//Напишите программу для поиска k-го наименьшего элемента в массиве с помощью алгоритмов МИНК и МИНСК.
//Определите, какой из алгоритмов оказывается эффективнее для различных длин массива и различных k.

#include "array.h"

//#define DEBUG

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
		std::cout << "Error! You enter empty system!\n";
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
	if (array.size() < k)
	{
		std::cout << "Error input MINK: array.size < k!\n";
		return -1;
	}

	if (array.size() == 1)
		return array[0];

	//Step 1. Разбиваем массив на пятерки
#ifdef DEBUG
	std::cout << "array = " << array << std::endl;
	std::cout << "k = " << k << std::endl;
#endif
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
#ifdef DEBUG
		std::cout << listOfArrays[i] << std::endl;
#endif 
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
		else
		{
			int temp_index = listOfArrays[i].size() - 1;
			median_arr.push_back(listOfArrays[i][temp_index]);
		}
	}

	delete[] listOfArrays;

#ifdef DEBUG
	std::cout << "Median_array = " << median_arr << std::endl;
#endif
	//Step 4. Ищем медиану /*M. m = MINK(M, n/10)*/. Для этого мы сортируем массив медиан и выбираем нужное число
	//int median_true = MINK(median_arr, countOfNumbers / (parts*2)); //parts = 5; 5*2=10. math!
	int median_true = 0;
	bubbleSort(median_arr.data(), countOfArrays);
	int index_for_median_true = countOfNumbers / (parts * 2);
	median_true = median_arr[index_for_median_true];

#ifdef DEBUG
	std::cout << "median = " << median_true << std::endl;
#endif

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

#ifdef DEBUG
	std::cout << "AM = " << numbers_less << " with size = " << numbers_less.size() << std::endl;
	std::cout << "AP = " << numbers_equal << " with size = " << numbers_equal.size() << std::endl;
	std::cout << "AB = " << numbers_larger << " with size = " << numbers_larger.size() << std::endl << std::endl;
#endif

	//Step 6. Проверка условий и выполнение нужного действия
	if (k <= numbers_less.size())
		return MINK(numbers_less, k);
	else if (k > numbers_less.size() && k <= (numbers_less.size() + numbers_equal.size()))
	{
		return median_true;
	}
	else if (k > (numbers_less.size() + numbers_equal.size()))
		return MINK(numbers_larger, k - numbers_less.size() - numbers_equal.size());
}

int MINSK(Array& array, int k)
{
	if (array.size() < k)
	{
		std::cout << "Error input MINK: array.size < k!\n";
		return -1;
	}

	if (array.size() == 1)
		return array[0];
#ifdef DEBUG
	std::cout << "array = " << array << std::endl;
	std::cout << "k = " << k << std::endl;
#endif
	int countOfNumbers = array.size();

	//Выбираем случайный элемент массива. Это будет медианой.
	std::srand(time(NULL));
	int a = 0;
	int b = countOfNumbers;
	int median_index = a + rand() % (b - a);
	int median_true = array[median_index];

#ifdef DEBUG
	std::cout << "median index randomized = " << median_index << " median = " << median_true << std::endl;
#endif

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

#ifdef DEBUG
	std::cout << "AM = " << numbers_less << " with size = " << numbers_less.size() << std::endl;
	std::cout << "AP = " << numbers_equal << " with size = " << numbers_equal.size() << std::endl;
	std::cout << "AB = " << numbers_larger << " with size = " << numbers_larger.size() << std::endl << std::endl;
#endif
	//Step 6. Проверка условий и выполнение нужного действия
	if (k <= numbers_less.size())
		return MINK(numbers_less, k);
	else if (k > numbers_less.size() && k <= (numbers_less.size() + numbers_equal.size()))
	{
		return median_true;
	}
	else if (k > (numbers_less.size() + numbers_equal.size()))
		return MINK(numbers_larger, k - numbers_less.size() - numbers_equal.size());
}

Array generateArray(int size, int maxRandom)
{
	std::srand(time(NULL));
	int* arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		int randomInt = rand() % maxRandom;
		arr[i] = randomInt;
	}
	Array randomArray(arr, size);
	delete[] arr;
	return randomArray;
}

void test()
{
	std::ofstream file("result_test1.txt");
	if (!file.is_open())
	{
		std::cout << "Error open file\n";
		exit(EXIT_FAILURE);
	}

	for (int sizeArray = 10000; sizeArray < 100000; sizeArray = sizeArray + 1000)
	{
		Array Adam = generateArray(sizeArray, 10000);
		//std::cout << "Array = " << Adam << std::endl;
		std::cout << "Size = " << sizeArray << std::endl;
		file << "Size = " << sizeArray << "\n";
		for (int k = 100; k <= 1000; k = k + 100)
		{
			unsigned int timeStart = clock();
			int mink = MINK(Adam, k);
			unsigned int timeEnd = clock();
			unsigned int timeTotal_MINK = timeEnd - timeStart;

			timeStart = clock();
			int minsk = MINSK(Adam, k);
			timeEnd = clock();
			unsigned int timeTotal_MINSK = timeEnd - timeStart;
			
			std::cout << "k = " << k << " mink = " << mink << " minsk = " << minsk << " time mink = " << timeTotal_MINK << " time minsk = " << timeTotal_MINSK << std::endl;
			file << "k = " << k << "	time mink | time minsk =  " << timeTotal_MINK << " | " << timeTotal_MINSK << "\n";
		}
	}

	file.close();
}

void workTest()
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
	while (k_num <= 0)
	{
		std::cout << "Entered k <= 0! Please, enter positive k: ";
		std::cin >> k_num;
		std::cout << std::endl;
	}

	unsigned int timeStart = clock();
	int mink = MINK(array, k_num);
	unsigned int timeEnd = clock();
	unsigned int timeTotal_MINK = timeEnd - timeStart;

	std::cout << "Result MINK = " << mink << std::endl << std::endl;

	timeStart = clock();
	int minsk = MINSK(array, k_num);
	timeEnd = clock();
	unsigned int timeTotal_MINSK = timeEnd - timeStart;

	std::cout << "Result MINSK = " << minsk << std::endl << std::endl;

	bubbleSort(array.data(), array.size());
	std::cout << std::endl << "sortedArray = " << array << " with size = " << array.size() << std::endl;
	std::cout << "k[" << k_num << "] = " << array[k_num - 1] << std::endl;
	std::cout << "Result MINK = " << mink << std::endl;
	std::cout << "Result MINSK = " << minsk << std::endl;
	std::cout << "MINK time = " << timeTotal_MINK << std::endl;
	std::cout << "MINSK time = " << timeTotal_MINSK << std::endl;

	//std::cout << array << std::endl;

	//bubbleSort(array.data(), array.size());

	//std::cout << "Sorted: " << array << std::endl;

	delete[] arr;
}

int main()
{
	workTest();
	
	//test();

	return 0;
}