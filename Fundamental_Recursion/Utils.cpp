#include <iostream>
#include <random>
#include <string>
#include "Utils.h"

void printNaturalNumber(const int n)
{
    if (n == 0)
        return;
    // "Digs down" until n = 0, then prints all natural numbers on the way back up
    printNaturalNumber(n-1);
    std::cout << n << " ";
}

int calculateFactorial(const int n)
{
    if (n <= 1)
        return 1;
     // "Digs down" until n <= 1, then multiplies by n for every step back up
    return n * calculateFactorial(n-1);
}

int power(const int base,const int exp)
{
    if (exp == 0 || base == 1 || base == 0)
        return 1;
    // "Digs down" until exp <= 0, then multiplies base with the base for every step back up
    return base * power(base, exp - 1);         // The simplest to write, not the most efficient - O(n)

    // int half = power(base / 2, exp);
    // if (exp % 2 == 0)
    //     return half * half;
    // else
    //     return base * half * half;           // More efficient implementation, reduces the recursive call by half
                                                // O(log n)

}

int fibonacci(const int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2); // O(2^n), each call spawns two more recursive calls
                                                // Could be optimised by using iteration instead of recursion
                                                // For loop would be O(n) since it takes the previous number, adding
                                                // current number, then stepping up until it has iterated n times
                                                // Linear growth instead of exponential
    // int current = 1;
    // int previous = 0;
    // for (int i = 2; i <= n; i++)
    // {
    //     int next = previous + current;
    //     previous = current;
    //     current = next;
    // }
    // return current;
}

int countOccurrences (const std::string& s, const char c)
{
    if (s.empty())
        return 0;
    const int count = (s[0] == c ? 1 : 0);
    return count + countOccurrences(s.substr(1), c);
    // O(n^2) since we have to make a new substring for every index of the original string
}

int findLargestElement(const int arr[], const int size)
{
    if (size <= 0)
        return 0;
    if (size == 1)
        return arr[0];
    const int mid = size / 2;
    const int leftMax = findLargestElement(arr, mid);
    const int rightMax = findLargestElement(arr + mid, size - mid);

    return (leftMax > rightMax) ? leftMax : rightMax;
    // O(n) time complexity, since we have to compare each element at least once
}

// Up to, not including, end
void traverseAsciiTable(const char start, const char end)
{
    if (start >= end)
        return;
    std::cout << start << " ";      // Reflects the building
    traverseAsciiTable(static_cast<char>(start + 1), end);

    std::cout << " ";               // Reflects the unwinding
}

// Helper funcs to populate and randomise input

void fillRandomArray(int arr[], const int size, const int minVal, const int maxVal)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);

    for (int i = 0; i < size; i++)
    {
        arr[i] = dist(gen);
    }
}

std::string makeRandomString(const int len, char minChar = 'a', char maxChar = 'z')
{
    if (len <= 0)
        return{};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minChar, maxChar);

    std::string s;
    s.reserve(len);
    for (int i = 0; i < len; i++)
        s.push_back(static_cast<char>(dist(gen)));
    return s;
}

int countOccurrences_index(const std::string& s, const char c, int index)
{
    if (index >= static_cast<int>(s.size()))
        return 0;
    const int hit = (s[index] == c ? 1 : 0);
    return hit + countOccurrences_index(s, c, index + 1);
}


