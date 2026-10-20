#include <iostream>
#include "constants.h"

#define MARGIN_MACRO 5 + 5            // macro: plain text substitution
constexpr int MARGIN_CONSTEXPR = 5 + 5; // typed, scoped, evaluated at compile time

enum Colour { Red, Green };           // unscoped enum
enum class Light { Red, Green };      // scoped enum class

int main()
{
    std::cout << "MARGIN_MACRO * 2     = " << MARGIN_MACRO * 2 << '\n';     // 5 + 5 * 2
    std::cout << "MARGIN_CONSTEXPR * 2 = " << MARGIN_CONSTEXPR * 2 << '\n'; // 10 * 2

    int c = Red;                                   // allowed: silent conversion to int
    std::cout << "unscoped Red as int  = " << c << '\n';
    // int l = Light::Red;                         // ERROR: no implicit conversion
    // if (Light::Green == 1) {}                   // ERROR: cannot compare with int
    Light l = Light::Green;
    std::cout << "enum class Green as int = " << static_cast<int>(l) << '\n';

    static_assert(BASE_FARE_PAISE[2] == 3000, "fare table checked at compile time");
    std::cout << "Outer fare = " << BASE_FARE_PAISE[static_cast<int>(Zone::Outer)] << " paise\n";
}
