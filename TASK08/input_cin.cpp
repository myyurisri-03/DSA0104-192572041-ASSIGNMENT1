#include <iomanip>
#include <iostream>
#include <limits>

void printRupees(long long paise)
{
    std::cout << "Rs " << paise / 100 << '.' << std::setw(2) << std::setfill('0')
              << paise % 100 << std::setfill(' ');
}
int readHour()
{
    int hour;
    while (true) {
        std::cout << "Enter hour (0-23): ";
        if (std::cin >> hour && hour >= 0 && hour <= 23) return hour;
        if (std::cin.eof()) return -1;
        std::cout << "  invalid input, try again\n";
        std::cin.clear();                                // reset fail state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                         // discard bad line
    }
}
int main()
{
    int hour = readHour();
    std::cout << "hour accepted: " << hour << '\n';
    long long paise = 3600;
    std::cout << "Journey report\n" << std::left << std::setw(10) << "Zone" << std::setw(8) << "Peak"
              << std::right << std::setw(12) << "Fare" << '\n';
    std::cout << std::left << std::setw(10) << "Outer" << std::setw(8) << "yes" << std::right
              << std::setw(9);
    printRupees(paise);
    std::cout << '\n';
    double rupees = paise / 100.0;
    std::cout << "fixed/setprecision(2): " << std::fixed << std::setprecision(2) << rupees << '\n';
}
