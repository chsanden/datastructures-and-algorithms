#include <chrono>
#include <iostream>
#include "Utils.h"

static void line(const char* title)
{
    std::cout << "\n======= " << title << "=======\n";
}

int main()
{
    line("Neutral numbers");
    printNaturalNumber(10);
    std::cout << "\n";


    line("Factorial");
    const int fact_expect[] = {
        1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800
    };
    bool ok_fact = true;
    for (int n = 0; n <= 10; ++n) {
        int r = calculateFactorial(n);
        std::cout << "n=" << n << " -> " << r
                  << (r == fact_expect[n] ? "  OK" : "  MISMATCH") << "\n";
        ok_fact &= (r == fact_expect[n]);
    }


    line ("Power");
    struct Case { int base, exp, expect; };
    const Case pow_cases[] = {
        {2,0,1}, {2,1,2}, {2,5,32}, {3,4,81}, {5,3,125}, {10,2,100}
    };
    bool ok_pow = true;
    for (auto c : pow_cases) {
        int r = power(c.base, c.exp);
        std::cout << c.base << "^" << c.exp << " = " << r
                  << (r == c.expect ? "  OK" : "  MISMATCH") << "\n";
        ok_pow &= (r == c.expect);

        line("Fibonacci");
        const int fib_expect[] = {0,1,1,2,3,5,8,13,21,34,55,89,144};
        bool ok_fib = true;
        for (int n = 0; n <= 12; ++n) {
            int r = fibonacci(n);
            std::cout << "F(" << n << ") = " << r
                      << (r == fib_expect[n] ? "  OK" : "  MISMATCH") << "\n";
            ok_fib &= (r == fib_expect[n]);
        }


        line("Count occurrences");
        std::string s = makeRandomString(2000, 'a', 'f');
        char target = 'c';
        int rec = countOccurrences(s, target);                                          //<--- recursive
        int ref = static_cast<int>(std::count(s.begin(), s.end(), target));
        std::cout << "recursive=" << rec << "  std::count=" << ref
                  << (rec == ref ? "  OK" : "  MISMATCH") << "\n";
        double t_rec_ms = time_ms([&]{ (void)countOccurrences(s, target); });
        std::cout << "perf (recursive substr): ~" << t_rec_ms << " ms\n";


        line ("Find largest element");
        constexpr int N = 100000;
        int* arr = new int[N];
        fillRandomArray(arr, N, -100000, 100000);
        double t_my_ms  = time_ms([&]{ (void)findLargestElement(arr, N); });
        int myMax = findLargestElement(arr, N);
        int stdMax = *std::max_element(arr, arr + N);
        std::cout << "myMax=" << myMax << "  stdMax=" << stdMax
                  << (myMax == stdMax ? "  OK" : "  MISMATCH") << "\n";
        std::cout << "perf (recursive): ~" << t_my_ms << " ms\n";
        delete[] arr;


        line("Traverse Ascii table");
        traverseAsciiTable('A', 'F');
        std::cout << "\n";


        line("Summary");
        std::cout << "Factorial: " << (ok_fact ? "OK" : "FAIL") << "\n";
        std::cout << "Power:     " << (ok_pow  ? "OK" : "FAIL") << "\n";
        std::cout << "Fibonacci: " << (ok_fib  ? "OK" : "FAIL") << "\n";

        return 0;
    }
}