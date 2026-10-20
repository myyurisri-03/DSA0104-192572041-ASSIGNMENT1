#include <chrono>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>

// Journey mix repeats every 12 journeys: base Rs, concession factor, peak factor, weekend factor
struct Mix { int baseRs; double concession; bool peak; };
constexpr Mix MIX[] = {{10,1.0,false},{20,1.0,true},{30,0.5,false},{30,0.5,true},{10,0.5,true},{20,1.0,false},
                       {30,1.0,true},{10,1.0,true},{20,0.5,false},{30,1.0,false},{20,0.5,true},{10,0.5,false}};
long long fairPaise(const Mix& m)
{
    long long base = m.baseRs * 100LL;
    if (m.concession < 1.0) base -= (base * 50 + 50) / 100;
    if (m.peak) base += (base * 20 + 50) / 100;
    return base;
}
double fareRupeesDouble(const Mix& m)           // same rule in double rupees
{
    double f = m.baseRs;
    f = f * m.concession;
    if (m.peak) f = f * 1.2;
    return f;
}

int main()
{
    std::cout << std::fixed;
    for (long long n : {20000LL, 500000LL, 3000000LL}) {
        long long sumPaise = 0; double sumD = 0.0; float sumF = 0.0f;
        int sumI = 0; bool overflowed = false; long long firstOverflowAt = -1;
        for (long long i = 0; i < n; ++i) {
            const Mix& m = MIX[i % 12];
            long long f = fairPaise(m);
            sumPaise += f;
            sumD += fareRupeesDouble(m);
            sumF += static_cast<float>(fareRupeesDouble(m));
            if (!overflowed && __builtin_add_overflow(sumI, static_cast<int>(f), &sumI)) {
                overflowed = true; firstOverflowAt = i + 1;
            }
        }
        double exactRs = sumPaise / 100.0;
        std::cout << "n = " << n << '\n';
        std::cout << "  long long paise total : " << sumPaise << " paise = Rs " << std::setprecision(2) << exactRs << '\n';
        std::cout << "  double rupees total   : " << std::setprecision(6) << sumD << "  (diff from exact "
                  << std::scientific << std::setprecision(3) << std::fabs(sumD - exactRs) << std::fixed << ")\n";
        std::cout << "  float rupees total    : " << std::setprecision(2) << sumF << "  (diff from exact "
                  << std::fabs(static_cast<double>(sumF) - exactRs) << ")\n";
        std::cout << "  int (32-bit) paise    : " << (overflowed ? "OVERFLOW at journey " + std::to_string(firstOverflowAt)
                                                              : std::string("fits")) << '\n';
    }
    std::cout << "INT_MAX = " << INT_MAX << '\n';

    // time per addition
    const long long N = 200000000LL;
    using ms = std::chrono::duration<double, std::milli>;
    volatile int vi = 0; volatile long long vl = 0; volatile double vd = 0.0;
    auto t0 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) vi = vi + 1;
    auto t1 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) vl = vl + 1;
    auto t2 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) vd = vd + 1.0;
    auto t3 = std::chrono::steady_clock::now();
    std::cout << std::setprecision(1);
    std::cout << "time for " << N << " additions: int " << ms(t1 - t0).count() << " ms, long long "
              << ms(t2 - t1).count() << " ms, double " << ms(t3 - t2).count() << " ms\n";
}
