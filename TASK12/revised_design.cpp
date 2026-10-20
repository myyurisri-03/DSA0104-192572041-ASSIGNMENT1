// Revised design: table-driven fares, separate discount rule, MonthlyPass class
#include <iomanip>
#include <iostream>
#include <string>

// ---- constants (single place) ---------------------------------------------
enum class Zone  { Inner, Middle, Outer, Airport };
enum class Rider { Adult, Student, Senior };
constexpr int ZONE_COUNT = 4;
constexpr long long BASE_FARE_PAISE[ZONE_COUNT] = {1000, 2000, 3000, 6000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;
constexpr int STUDENT_CONCESSION_PERCENT = 50;
constexpr int SENIOR_CONCESSION_PERCENT = 50;
constexpr long long MIN_BALANCE_PAISE = 5000;

inline int idx(Zone z) { return static_cast<int>(z); }
long long percentOf(long long amount, int percent)
{
    return (amount * percent + 50) / 100;
}
bool isPeak(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }

// ---- pricing: weekend discount REPLACES the peak surcharge ------------------
long long fare(Zone z, int hour, bool weekend, Rider r)
{
    long long f = BASE_FARE_PAISE[idx(z)];
    if (r == Rider::Student) f -= percentOf(f, STUDENT_CONCESSION_PERCENT);
    else if (r == Rider::Senior) f -= percentOf(f, SENIOR_CONCESSION_PERCENT);
    if (weekend)              f -= percentOf(f, WEEKEND_DISCOUNT_PERCENT);
    else if (isPeak(hour))    f += percentOf(f, PEAK_SURCHARGE_PERCENT);
    return f;
}

// ---- monthly pass: unlimited journeys in two chosen zones -------------------
class MonthlyPass {
public:
    MonthlyPass(Zone a, Zone b, int month) : a_{a}, b_{b}, month_{month} {}
    bool covers(Zone farthest, int month) const
    {
        return month == month_ && (farthest == a_ || farthest == b_);
    }
private:
    Zone a_, b_; int month_;
};

class SmartCard {
public:
    explicit SmartCard(long long initial) : balance_{initial > 0 ? initial : 0} {}
    void attachPass(const MonthlyPass& p) { pass_ = p; hasPass_ = true; }
    bool canTravel(long long f) const
    {
        return f >= 0 && balance_ - f >= MIN_BALANCE_PAISE;
    }
    // true if the journey is allowed; 'charged' returns the amount deducted
    bool travel(Zone z, int hour, bool weekend, Rider r, int month,
                long long& charged)
    {
        if (hasPass_ && pass_.covers(z, month)) { charged = 0; return true; }
        long long f = fare(z, hour, weekend, r);
        if (!canTravel(f)) { charged = 0; return false; }
        balance_ -= f; charged = f; return true;
    }
    long long balance() const { return balance_; }
private:
    long long balance_;
    MonthlyPass pass_{Zone::Inner, Zone::Inner, 0};  // used only if hasPass_
    bool hasPass_ = false;
};

// ---- table-driven tests ---------------------------------------------------
struct Case { const char* name; Zone z; int hour; bool weekend; Rider r; long long expected; };

int main()
{
    const Case cases[] = {
        {"Airport weekday off-peak",            Zone::Airport, 12, false, Rider::Adult,   6000},
        {"Airport weekday peak (9:00)",         Zone::Airport,  9, false, Rider::Adult,   7200},
        {"Airport weekend (peak hour ignored)", Zone::Airport,  9, true,  Rider::Adult,   5400},
        {"Inner weekend off-peak",              Zone::Inner,   12, true,  Rider::Adult,    900},
        {"Inner weekend at 8:00 (no surcharge)",Zone::Inner,    8, true,  Rider::Adult,    900},
        {"Outer weekday peak 17:00",            Zone::Outer,   17, false, Rider::Adult,   3600},
        {"Outer weekday 20:00 off-peak",        Zone::Outer,   20, false, Rider::Adult,   3000},
        {"Student Airport weekend",             Zone::Airport, 12, true,  Rider::Student, 2700},
        {"Senior Middle weekday peak",          Zone::Middle,   9, false, Rider::Senior,  1200},
    };
    int pass = 0, total = 0;
    std::cout << std::left << std::setw(40) << "Fare test" << std::setw(10) << "Expected"
              << std::setw(10) << "Actual" << "Result\n";
    for (const Case& c : cases) {
        long long a = fare(c.z, c.hour, c.weekend, c.r);
        ++total; pass += (a == c.expected);
        std::cout << std::setw(40) << c.name << std::setw(10) << c.expected << std::setw(10) << a
                  << (a == c.expected ? "PASS" : "FAIL") << '\n';
    }

    // pass tests: pass for Outer + Airport in month 6
    SmartCard card{9000};
    card.attachPass(MonthlyPass{Zone::Outer, Zone::Airport, 6});
    long long charged = -1;
    struct P { const char* name; Zone z; int month; bool allowed; long long charge; long long balAfter; } ps[] = {
        {"pass: Outer in month 6 is free",           Zone::Outer,   6, true,  0,    9000},
        {"pass: Airport in month 6 is free",         Zone::Airport, 6, true,  0,    9000},
        {"pass: Inner not covered, pays Rs 10",      Zone::Inner,   6, true,  1000, 8000},
        {"pass: Outer in month 7 (expired) pays",    Zone::Outer,   7, true,  3000, 5000},
        {"pass expired: Airport denied (low balance)", Zone::Airport, 7, false, 0,  5000},
    };
    for (const P& p : ps) {
        bool ok = card.travel(p.z, 12, false, Rider::Adult, p.month, charged);
        bool good = (ok == p.allowed) && charged == p.charge && card.balance() == p.balAfter;
        ++total; pass += good;
        std::cout << std::setw(52) << p.name << "charged " << std::setw(5) << charged << " balance "
                  << std::setw(5) << card.balance() << (good ? "  PASS" : "  FAIL") << '\n';
    }
    SmartCard lowCard{3000};                             // Rs 30 only, but holds a valid pass
    lowCard.attachPass(MonthlyPass{Zone::Middle, Zone::Outer, 6});
    bool ok = lowCard.travel(Zone::Outer, 12, false, Rider::Adult, 6, charged) && charged == 0;
    ++total; pass += ok;
    std::cout << std::setw(52) << "pass holder with Rs 30 rides Outer free" << "charged " << std::setw(5)
              << charged << " balance " << std::setw(5) << lowCard.balance() << (ok ? "  PASS" : "  FAIL") << '\n';
    std::cout << "\n" << pass << " / " << total << " tests passed\n";
    return pass == total ? 0 : 1;
}
