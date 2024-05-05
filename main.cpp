#include <iostream>
#include <math.h>

#include <fstream> //äëÿ óäîáíîãî ââîäà ìàññèâà èç ôàéëà
#include <string> //òàêæå äëÿ óäîáíîãî ââîäà ìàññèâà
//Íàïèøèòå ïðîãðàììó äëÿ ïîèñêà k-ãî íàèìåíüøåãî ýëåìåíòà â ìàññèâå ñ ïîìîùüþ àëãîðèòìîâ ÌÈÍÊ è ÌÈÍÑÊ.
//Îïðåäåëèòå, êàêîé èç àëãîðèòìîâ îêàçûâàåòñÿ ýôôåêòèâíåå äëÿ ðàçëè÷íûõ äëèí ìàññèâà è ðàçëè÷íûõ k.

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

int MINK(Array& array, int k)
{
	//Step 1. Разбить массив на пятерки

	int countOfNumbers = array.size();
	int countOfArrays = countOfNumbers / 5;
	int** listOfArrays = new int* [countOfArrays];
	int index = 0;
	for (int i = 0; i < countOfArrays; i++)
	{
		if (countOfNumbers > 5)
		int* arr = new int[5];
		for ()
	}

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

	Array array(newSize, arr);

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

	std::cout << array << std::endl;
	
	delete[] arr;
	return 0;
}