#include <iostream>
int main()
{
    int i = 5;
    int a = i++;   // a = 5, i = 6
    int j = 5;
    int b = ++j;   // b = 6, j = 6
    std::cout << "i++ -> " << a << " (i=" << i << "), ++j -> " << b << " (j=" << j << ")\n";
    int m = 5;
    m = m++;       // do NOT write this (unspecified/undefined before C++17)
    std::cout << "m = m++ gives m = " << m << " (compiler dependent habit - avoid)\n";
}
