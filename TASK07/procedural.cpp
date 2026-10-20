// Procedural style: global variables + free functions
#include <iostream>
long long balance = 10000;            // anybody can change this
constexpr long long MIN_BALANCE = 5000;

long long fareOf(int zone, bool peak)
{
    long long base = (zone == 0) ? 1000 : (zone == 1) ? 2000 : 3000;
    return peak ? base + base * 20 / 100 : base;
}
bool canTravel(long long f) { return balance - f >= MIN_BALANCE; }

int main()
{
    int zones[] = {0, 2, 1};
    bool peaks[] = {false, true, false};
    for (int i = 0; i < 3; ++i) {
        long long f = fareOf(zones[i], peaks[i]);
        if (canTravel(f)) { balance -= f; std::cout << "paid " << f << " balance " << balance << '\n'; }
        else std::cout << "denied, balance " << balance << '\n';
    }
    balance = -999;                   // nothing stops this
    std::cout << "after careless assignment balance = " << balance << '\n';
}
