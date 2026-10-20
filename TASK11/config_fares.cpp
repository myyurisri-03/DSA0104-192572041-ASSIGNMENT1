// Alternative: fare table read from a configuration file at start-up
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main()
{
    auto t0 = std::chrono::steady_clock::now();
    std::ifstream in("fares.cfg");
    std::map<std::string, long long> table;
    std::string zone; long long paise;
    while (in >> zone >> paise) {
        if (paise <= 0) { std::cerr << "bad fare for " << zone << '\n'; return 1; } // validate at run time
        table[zone] = paise;
    }
    auto t1 = std::chrono::steady_clock::now();
    std::cout << "read " << table.size() << " fares in "
              << std::chrono::duration<double, std::micro>(t1 - t0).count() << " microseconds\n";
    for (auto& [z, p] : table) std::cout << "  " << z << " = " << p << " paise\n";
    std::cout << "sizeof(long long) * " << table.size() << " = " << sizeof(long long) * table.size()
              << " bytes of payload (plus map overhead)\n";
}
