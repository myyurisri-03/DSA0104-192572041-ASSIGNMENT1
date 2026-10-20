// Alternative: public data member -> any code can break the rule
#include <iostream>
struct SmartCard { long long balance; };

int main()
{
    SmartCard card{10000};
    card.balance -= 9500;                       // no check: leaves Rs 5 (rule needs Rs 50)
    std::cout << "balance after careless deduction = " << card.balance << " paise (rule broken)\n";
    card.balance -= 2000;                       // goes negative
    std::cout << "balance after second deduction   = " << card.balance << " paise (negative!)\n";
}
