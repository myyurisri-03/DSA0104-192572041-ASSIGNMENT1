// Peak check: expression vs lookup table bool peak[24]
#include <chrono>
#include <iostream>

bool peakExpr(int h) { return (h >= 8 && h < 10) || (h >= 17 && h < 20); }

int main()
{
    bool peak[24] = {};
    for (int h = 0; h < 24; ++h) peak[h] = peakExpr(h);   // built once from the rule

    bool same = true;
    for (int h = 0; h < 24; ++h) same = same && (peak[h] == peakExpr(h));
    std::cout << "table == expression for all 24 hours: " << std::boolalpha << same << '\n';
    std::cout << "boundary: 8->" << peak[8] << " 10->" << peak[10] << " 17->" << peak[17]
              << " 20->" << peak[20] << '\n';
    std::cout << "sizeof(peak) = " << sizeof(peak) << " bytes\n";

    const int N = 100000000;
    volatile int sink = 0;
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) sink = sink + peakExpr(i % 24);
    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) sink = sink + peak[i % 24];
    auto t2 = std::chrono::steady_clock::now();
    using ms = std::chrono::duration<double, std::milli>;
    std::cout << "expression: " << ms(t1 - t0).count() << " ms for " << N << " checks\n";
    std::cout << "table     : " << ms(t2 - t1).count() << " ms for " << N << " checks\n";
}
