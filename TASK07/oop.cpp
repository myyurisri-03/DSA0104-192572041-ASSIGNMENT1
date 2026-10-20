// Object-oriented style: SmartCard keeps balance private
#include <iostream>

class SmartCard {
public:
    static constexpr long long MIN_BALANCE = 5000;       // single place for the rule
    explicit SmartCard(long long initial) : balance_{initial >= 0 ? initial : 0} {}
    bool canTravel(long long fare) const
    {
        return fare >= 0 && balance_ - fare >= MIN_BALANCE;
    }
    bool deduct(long long fare)                  // only way to reduce the balance
    {
        if (!canTravel(fare)) return false;
        balance_ -= fare;
        return true;
    }
    bool recharge(long long amount)
    {
        if (amount <= 0) return false;           // negative recharge rejected
        balance_ += amount;
        return true;
    }
    long long balance() const { return balance_; }
private:
    long long balance_;
};

long long fareOf(int zone, bool peak)
{
    long long base = (zone == 0) ? 1000 : (zone == 1) ? 2000 : 3000;
    return peak ? base + base * 20 / 100 : base;
}

int main()
{
    SmartCard card{10000};
    int zones[] = {0, 2, 1};
    bool peaks[] = {false, true, false};
    for (int i = 0; i < 3; ++i) {
        long long f = fareOf(zones[i], peaks[i]);
        if (card.deduct(f)) std::cout << "paid " << f << " balance " << card.balance() << '\n';
        else std::cout << "denied, balance " << card.balance() << '\n';
    }
    std::cout << "recharge(-500) accepted? " << std::boolalpha << card.recharge(-500) << '\n';
    // card.balance_ = -999;   // ERROR: 'balance_' is private
    std::cout << "balance still " << card.balance() << '\n';
}
