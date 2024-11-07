#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <memory>

void printNumbers(const int* numbers, int size)
{
    std::cout << "Current numbers: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
}

void resetNumbers(int* numbers, int size)
{
    std::srand(std::time(nullptr));
    for (int i = 0; i < size; i++)
    {
        numbers[i] = std::rand() % 100; // Generate random numbers between 0 and 99
    }
    std::cout << "Numbers reset to random values." << std::endl;
}

void printNumber(int32_t n)
{
    // Code for the injected function
    std::cout << "The number is: " << n << std::endl;
}

int main()
{
    // Print address of number printer fn
    std::cout << "Address of printNumber: " << &printNumber << std::endl;

    size_t tempDirStrLen = 255;
    auto tempDirStr = new char[tempDirStrLen];
    _dupenv_s(&tempDirStr, &tempDirStrLen, "TEMP");
    auto tempFileStr = std::string(tempDirStr) + "\\hhfdgoi438539.tmp";
    std::cout << "Temp file path: " << tempFileStr << std::endl;
    
    // Create the tempFileStr
    std::ofstream tempFile;
    tempFile.open(tempFileStr, std::ios::out | std::ofstream::trunc);
    if (tempFile.is_open())
    {
        tempFile << &printNumber;
        tempFile.close();
        std::cout << "Temp file created successfully for fn address." << std::endl;
    }
    else
    {
        std::cout << "Failed to create temp file." << std::endl;
    }

    delete[] tempDirStr;

    const int ARRAY_SIZE = 10;
    auto numbers = new int[ARRAY_SIZE];
    resetNumbers(numbers, ARRAY_SIZE);

    int choice;
    do
    {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Print numbers" << std::endl;
        std::cout << "2. Reset numbers" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "\nEnter your choice:\n";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            printNumbers(numbers, ARRAY_SIZE);
            break;
        case 2:
            resetNumbers(numbers, ARRAY_SIZE);
            printNumbers(numbers, ARRAY_SIZE); // Print the numbers after resetting
            break;
        case 0:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
