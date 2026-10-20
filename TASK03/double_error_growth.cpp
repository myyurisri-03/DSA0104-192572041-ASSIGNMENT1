// Alternative: money as double rupees. Measure how the error grows when n fares are added.
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << std::fixed << std::setprecision(9);
    std::cout << "n, exact_rupees(paise/100), double_sum, abs_error\n";
    for (long long n : {20000LL, 500000LL, 3000000LL, 30000000LL}) {
        long long paise = 0;      // fare Rs 0.10 (10 paise) added n times
        double rupees = 0.0;
        for (long long i = 0; i < n; ++i) { paise += 10; rupees += 0.10; }
        double exact = static_cast<double>(paise) / 100.0;
        std::cout << n << ", " << exact << ", " << rupees << ", " << std::fabs(rupees - exact) << '\n';
    }
}
