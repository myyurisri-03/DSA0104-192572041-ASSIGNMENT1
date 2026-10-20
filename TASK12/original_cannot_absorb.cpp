// Worked example: the ORIGINAL switch-based design meeting the new requirements
#include <iostream>
enum class Zone { Inner, Middle, Outer };                // Airport does not exist here
constexpr int BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
long long fare(Zone z, bool peak)
{
    long long base = 0;
    switch (z) {
    case Zone::Inner:  base = BASE_PAISE[0]; break;
    case Zone::Middle: base = BASE_PAISE[1]; break;
    case Zone::Outer:  base = BASE_PAISE[2]; break;
    default:           base = 0; break;
    }
    if (peak) base += base * PEAK_SURCHARGE_PERCENT / 100;
    return base;
}
class SmartCard {                                        // original Task 7 class
public:
    explicit SmartCard(long long b) : balance_{b} {}
    bool canTravel(long long f) const { return f >= 0 && balance_ - f >= 5000; }
private:
    long long balance_;
};
int main()
{
    Zone airport = static_cast<Zone>(3);                 // forced in: enum has no Airport
    std::cout << "Airport journey fare with old code = " << fare(airport, false) << " paise (should be 6000)\n";
    std::cout << "Weekend Inner at peak hour: old code can only say peak=true -> "
              << fare(Zone::Inner, true) << " paise (should be 900)\n";
    SmartCard lowCard{3000};                              // Rs 30 on the card, valid monthly pass
    std::cout << "Pass holder with Rs 30: canTravel(0) = " << std::boolalpha << lowCard.canTravel(0)
              << " (a free journey is wrongly denied)\n";
    std::cout << "Old BASE_PAISE[3] would read past the array (undefined behaviour) - not executed\n";
}
