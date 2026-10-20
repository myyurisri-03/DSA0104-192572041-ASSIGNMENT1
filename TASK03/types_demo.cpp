#include <climits>
#include <cfloat>
#include <cstdio>
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "--- sizeof on this system ---\n";
    std::cout << "bool " << sizeof(bool) << ", char " << sizeof(char) << ", int " << sizeof(int)
              << ", unsigned " << sizeof(unsigned) << ", long long " << sizeof(long long)
              << ", float " << sizeof(float) << ", double " << sizeof(double) << '\n';
    std::cout << "--- ranges (<climits>) ---\n";
    std::cout << "INT_MAX = " << INT_MAX << "\nINT_MIN = " << INT_MIN << "\nUINT_MAX = " << UINT_MAX
              << "\nLLONG_MAX = " << LLONG_MAX << "\nCHAR_BIT = " << CHAR_BIT << '\n';

    std::cout << "--- precision problem with double rupees ---\n";
    double a = 0.1 + 0.2;
    std::cout << std::setprecision(17) << "0.1 + 0.2 = " << a << "\n(0.1 + 0.2 == 0.3) is "
              << std::boolalpha << (a == 0.3) << '\n';
    double rupees = 0.29;
    int paiseWrong = static_cast<int>(rupees * 100);  // truncates 28.999999...
    std::cout << "0.29 * 100 = " << rupees * 100 << " -> int = " << paiseWrong << " (expected 29)\n";
    long long paise = 29;                              // integer paise: exact
    std::cout << "integer paise: " << paise << '\n';

    std::cout << "--- overflow: day collection at network scale ---\n";
    long long perJourney = 3600;                       // worst case Rs 36.00 in paise
    long long journeys   = 3000000;
    long long total      = perJourney * journeys;
    std::cout << "true total (long long) = " << total << " paise\n";
    std::cout << "INT_MAX                = " << INT_MAX << "\n";
    std::cout << "fits in int? " << (total <= INT_MAX) << '\n';
    int wrapped = static_cast<int>(static_cast<unsigned>(total)); // what a wrap-around would show
    std::cout << "value if stored in 32-bit int (wrapped) = " << wrapped << '\n';
}
