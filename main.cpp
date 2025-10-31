#include <lib.hpp>

enum class Color { RED, BLACK, GREEN };

struct spin {
    int number;
    Color color;  
};

std::ostream& operator<<(std::ostream& os, Color c) {
    switch (c) {
        case Color::RED:   return os << "RED";
        case Color::BLACK: return os << "BLACK";
        case Color::GREEN: return os << "GREEN";
    }
    return os << '?';
}
std::ostream& operator<<(std::ostream& os, const spin& s) {
    return os << s.number << " [" << s.color << "]";
}

spin roll() {
    static constexpr std::array<Color, 37> COLORS = {
        Color::GREEN,   // 0
        Color::RED,     // 1
        Color::BLACK,   // 2
        Color::RED,     // 3
        Color::BLACK,   // 4
        Color::RED,     // 5
        Color::BLACK,   // 6
        Color::RED,     // 7
        Color::BLACK,   // 8
        Color::RED,     // 9
        Color::BLACK,   // 10 
        Color::BLACK,   // 11
        Color::RED,     // 12
        Color::BLACK,   // 13
        Color::RED,     // 14
        Color::BLACK,   // 15
        Color::RED,     // 16
        Color::BLACK,   // 17
        Color::RED,     // 18
        Color::RED,     // 19
        Color::BLACK,   // 20
        Color::RED,     // 21
        Color::BLACK,   // 22
        Color::RED,     // 23
        Color::BLACK,   // 24
        Color::RED,     // 25
        Color::BLACK,   // 26
        Color::RED,     // 27
        Color::BLACK,   // 28
        Color::BLACK,   // 29
        Color::RED,     // 30
        Color::BLACK,   // 31
        Color::RED,     // 32
        Color::BLACK,   // 33
        Color::RED,     // 34
        Color::BLACK,   // 35
        Color::RED      // 36
    };

    static thread_local std::mt19937 rng(std::random_device{}());
    static thread_local std::uniform_int_distribution<int> dist(0, 36);
    int n = dist(rng);
    return spin{ n, COLORS[n] };
}


int main() {
    int betAmomunt, betNumber;

    std::cout << "Enter bet number (0-36): ";
    std::cin >> betNumber;
    spin rollOut = roll();
    if (rollOut.number == betNumber) {
        std::cout << "You won! Rolled: " << rollOut << "\n";
    } else {
        std::cout << "You lost. Rolled: " << rollOut << "\n";
    }

    system("pause");
    return 0;
}
