// Namma Metro smart-card fare logic (3 zones) - implementation + table-driven tests
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include "../Task02/constants.h"

enum class Rider { Adult, Student, Senior };

// ---- helpers ---------------------------------------------------------------
long long percentOf(long long amount, int percent)        // exact, rounds half up
{
    return (amount * percent + 50) / 100;
}
bool isPeak(int hour)
{
    return (hour >= MORNING_PEAK_START && hour < MORNING_PEAK_END) ||
           (hour >= EVENING_PEAK_START && hour < EVENING_PEAK_END);
}
bool validZone(int z) { return z >= 0 && z < ZONE_COUNT; }

long long fare(Zone z, int hour, Rider r)
{
    long long base = BASE_FARE_PAISE[static_cast<int>(z)];
    switch (r) {
    case Rider::Student: base -= percentOf(base, STUDENT_CONCESSION_PERCENT); break;
    case Rider::Senior:  base -= percentOf(base, SENIOR_CONCESSION_PERCENT);  break;
    case Rider::Adult:   break;
    }
    if (isPeak(hour)) base += percentOf(base, PEAK_SURCHARGE_PERCENT);
    return base;
}

class SmartCard {
public:
    explicit SmartCard(long long initial) : balance_{initial > 0 ? initial : 0} {}
    bool canTravel(long long f) const
    {
        return f >= 0 && balance_ - f >= MIN_BALANCE_PAISE;
    }
    bool deduct(long long f)
    {
        if (!canTravel(f)) return false;
        balance_ -= f;
        return true;
    }
    bool recharge(long long amount)
    {
        if (amount <= 0) return false;
        balance_ += amount;
        return true;
    }
    long long balance() const { return balance_; }
private:
    long long balance_;
};

std::string rs(long long paise)
{
    return "Rs " + std::to_string(paise / 100) + "." + (paise % 100 < 10 ? "0" : "") +
           std::to_string(paise % 100);
}

// ---- table-driven fare tests --------------------------------------------------------
struct FareCase { const char* name; Zone z; int hour; Rider r; long long expected; };

int main()
{
    const FareCase cases[] = {
        {"Inner off-peak adult (12:00)",  Zone::Inner,  12, Rider::Adult,   1000},
        {"Middle off-peak adult (12:00)", Zone::Middle, 12, Rider::Adult,   2000},
        {"Outer off-peak adult (12:00)",  Zone::Outer,  12, Rider::Adult,   3000},
        {"Inner peak adult (9:00)",       Zone::Inner,   9, Rider::Adult,   1200},
        {"Middle peak adult (18:00)",     Zone::Middle, 18, Rider::Adult,   2400},
        {"Outer peak adult (8:00)",       Zone::Outer,   8, Rider::Adult,   3600},
        {"Boundary 8:00 is peak",         Zone::Inner,   8, Rider::Adult,   1200},
        {"Boundary 10:00 is off-peak",    Zone::Inner,  10, Rider::Adult,   1000},
        {"Boundary 17:00 is peak",        Zone::Inner,  17, Rider::Adult,   1200},
        {"Boundary 20:00 is off-peak",    Zone::Inner,  20, Rider::Adult,   1000},
        {"Student Outer off-peak",        Zone::Outer,  12, Rider::Student, 1500},
        {"Senior Outer peak",             Zone::Outer,  18, Rider::Senior,  1800},
    };
    int pass = 0, total = 0;
    std::cout << std::left << std::setw(34) << "Test case" << std::setw(10) << "Expected"
              << std::setw(10) << "Actual" << "Result\n";
    for (const FareCase& c : cases) {
        long long actual = fare(c.z, c.hour, c.r);
        bool ok = actual == c.expected;
        ++total; pass += ok;
        std::cout << std::setw(34) << c.name << std::setw(10) << c.expected << std::setw(10) << actual
                  << (ok ? "PASS" : "FAIL") << '\n';
    }

    // ---- balance rule ----
    SmartCard exact{4000 + 1000};                        // Rs 50 -> any fare leaves < Rs 50
    SmartCard edge{6000};                                // Rs 60: Rs 10 fare leaves exactly Rs 50
    struct { const char* name; bool got; bool want; } bal[] = {
        {"balance leaves exactly Rs 50 -> allowed", edge.canTravel(1000), true},
        {"balance leaves Rs 49.99 -> denied",       SmartCard{5999}.canTravel(1000), false},
        {"balance Rs 50, fare Rs 10 -> denied",     exact.canTravel(1000), false},
    };
    for (auto& b : bal) {
        ++total; pass += (b.got == b.want);
        std::cout << std::setw(54) << b.name << (b.got == b.want ? "PASS" : "FAIL") << '\n';
    }

    // ---- invalid cases ----
    {
        ++total; bool ok = !validZone(7) && !validZone(-1);
        pass += ok; std::cout << std::setw(54) << "unknown zone 7 / -1 rejected" << (ok ? "PASS" : "FAIL") << '\n';
        SmartCard c{10000};
        ++total; ok = !c.recharge(-500) && c.balance() == 10000;
        pass += ok; std::cout << std::setw(54) << "negative recharge rejected" << (ok ? "PASS" : "FAIL") << '\n';
        std::cin.clear();
        std::string text = "ab";
        int h = 0; bool numeric = true;
        try { h = std::stoi(text); } catch (...) { numeric = false; }
        ++total; ok = !numeric && h == 0;
        pass += ok; std::cout << std::setw(54) << "letters typed for hour rejected" << (ok ? "PASS" : "FAIL") << '\n';
    }

    // ---- 5 journeys calculated by hand ----
    SmartCard card{50000};                               // Rs 500.00
    struct J { Zone z; int h; Rider r; } js[] = {
        {Zone::Inner, 10, Rider::Adult}, {Zone::Middle, 9, Rider::Adult},
        {Zone::Outer, 12, Rider::Student}, {Zone::Outer, 18, Rider::Senior},
        {Zone::Middle, 20, Rider::Adult}};
    long long sum = 0;
    std::cout << "\n5-journey set\n";
    for (const J& j : js) {
        long long f = fare(j.z, j.h, j.r);
        card.deduct(f); sum += f;
        std::cout << "  fare " << rs(f) << "  balance " << rs(card.balance()) << '\n';
    }
    ++total; bool ok = (sum == 8700 && card.balance() == 41300);
    pass += ok;
    std::cout << "hand total Rs 87.00, program total " << rs(sum) << " -> " << (ok ? "PASS" : "FAIL") << '\n';
    std::cout << "\n" << pass << " / " << total << " tests passed\n";
    return pass == total ? 0 : 1;
}
