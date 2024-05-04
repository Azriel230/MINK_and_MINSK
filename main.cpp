#include <iostream>
#include <math.h>

#include <fstream> //для удобного ввода массива из файла
#include <string> //также для удобного ввода массива
//Напишите программу для поиска k-го наименьшего элемента в массиве с помощью алгоритмов МИНК и МИНСК.
//Определите, какой из алгоритмов оказывается эффективнее для различных длин массива и различных k.

int sizeOfArray(int* arr)
{
	std::cout << typeid(sizeof(arr) / sizeof(*arr)).name();
	return (sizeof(arr) / sizeof(*arr));
}

int MINK(int* arr, int k1)
{
	return 0;
}

int MINSK()
{
	return 0;
}

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

void printArray(int* arr, int size1)
{
	int size = sizeOfArray(arr);
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

int main()
{
	int sizeArray = calculateSizeArray();
	int* array = new int[sizeArray];

	std::ifstream file("input.txt");
	if (!file.is_open())
	{
		std::cout << "Error open file\n";
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < sizeArray; i++)
		file >> array[i];	

	file.close();
	
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

	printArray(array, sizeArray);

	delete [] array;
	return 0;
}