// Alternative: getline + stoi inside try/catch
#include <iostream>
#include <string>
#include <stdexcept>

int main()
{
    std::string line;
    while (true) {
        std::cout << "Enter hour (0-23): ";
        if (!std::getline(std::cin, line)) return 0;
        try {
            std::size_t used = 0;
            int hour = std::stoi(line, &used);
            if (used != line.size()) throw std::invalid_argument("trailing characters");
            if (hour < 0 || hour > 23) throw std::out_of_range("hour out of range");
            std::cout << "hour accepted: " << hour << '\n';
            break;
        } catch (const std::exception& e) {
            std::cout << "  invalid input (" << e.what() << "), try again\n";
        }
    }
}
