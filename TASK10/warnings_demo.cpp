// Deliberately written with typical beginner problems to see what -Wall -Wextra reports
#include <iostream>
int main()
{
    int unusedVariable = 5;               // -Wunused-variable
    int s = -1;
    unsigned int u = 1;
    if (s < u) std::cout << "less\n";     // -Wsign-compare
    int n = 3;
    int total = n++ + n++;                // -Wsequence-point / unsequenced modification
    std::cout << total << '\n';
    int x;                                // used before set: -Wuninitialized
    std::cout << x << '\n';
}
