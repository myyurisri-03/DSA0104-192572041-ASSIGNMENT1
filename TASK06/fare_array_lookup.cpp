// Alternative: array indexed by zone instead of a switch
#include <iostream>
enum class Zone { Inner, Middle, Outer, Airport };            // a 4th zone = one more array entry
constexpr long long FARE[] = {1000, 2000, 3000, 6000};
constexpr int PEAK_PCT = 20;
long long fare(Zone z, bool peak)
{
    long long base = FARE[static_cast<int>(z)];               // O(1) lookup, no switch
    return peak ? base + base * PEAK_PCT / 100 : base;
}
int main()
{
    std::cout << fare(Zone::Inner, false) << ' ' << fare(Zone::Outer, true) << ' '
              << fare(Zone::Airport, false) << '\n';
}
