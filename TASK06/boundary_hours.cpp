// Peak rule at the boundaries: 8:00 and 17:00 are peak, 10:00 and 20:00 are NOT.
#include <iostream>
#include "../Task02/constants.h"

bool isPeak(int hour)
{
    return (hour >= MORNING_PEAK_START && hour < MORNING_PEAK_END) ||
           (hour >= EVENING_PEAK_START && hour < EVENING_PEAK_END);
}
int main()
{
    for (int h : {7, 8, 9, 10, 16, 17, 19, 20})
        std::cout << "hour " << h << ":00 -> " << (isPeak(h) ? "peak" : "off-peak") << '\n';
    std::cout << "Outer fare at 10:00 = " << BASE_FARE_PAISE[2] << " paise (no surcharge)\n";
    std::cout << "Outer fare at 20:00 = " << BASE_FARE_PAISE[2] << " paise (no surcharge)\n";
}
