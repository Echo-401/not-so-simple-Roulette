#include <lib.hpp>

enum class Color { RED, BLACK, GREEN };
enum class bettype {STRAIGHT, SPLIT, STREET, CORNERR, SIXLINE, TRIO, BASKET, COLUMN, DOZEN, COLOR, PARITY, HIGHLOW, EXIT};
enum class betKeyword {HIGH, LOW, EVEN, ODD, RED, BLACK, GREEN};

struct token {
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
std::ostream& operator<<(std::ostream& os, const token& s) {
    return os << s.number << " [" << s.color << "]";
}
std::istream& operator>>(std::istream& in, bettype& type) {
    std::string token;
    in >> token;
    for (auto& c : token) c = std::tolower(c);

    if (token == "straight") type = bettype::STRAIGHT;
    else if (token == "split") type = bettype::SPLIT;
    else if (token == "street") type = bettype::STREET;
    else if (token == "corner") type = bettype::CORNERR;
    else if (token == "sixline") type = bettype::SIXLINE;
    else if (token == "trio") type = bettype::TRIO;
    else if (token == "basket") type = bettype::BASKET;
    else if (token == "column") type = bettype::COLUMN;
    else if (token == "dozen") type = bettype::DOZEN;
    else if (token == "color") type = bettype::COLOR;
    else if (token == "parity") type = bettype::PARITY;
    else if (token == "highlow") type = bettype::HIGHLOW;
    else if (token == "exit") type = bettype::EXIT;
    else in.setstate(std::ios::failbit); // mark as invalid

    return in;
}
std::istream& operator>>(std::istream& in, betKeyword& type) {
    std::string token;
    in >> token;
    for (auto& c : token) c = std::tolower(c);

    if (token == "high") type = betKeyword::HIGH;
    else if (token == "low") type = betKeyword::LOW;
    else if (token == "even") type = betKeyword::EVEN;
    else if (token == "odd") type = betKeyword::ODD;
    else if (token == "red") type = betKeyword::RED;
    else if (token == "green") type = betKeyword::GREEN;
    else if (token == "black") type = betKeyword::BLACK;
    else in.setstate(std::ios::failbit); // mark as invalid

    return in;
}
bool operator==(betKeyword ihs, Color rhs) {
    switch (ihs) {
        case betKeyword::RED:   return rhs == Color::RED;
        case betKeyword::BLACK: return rhs == Color::BLACK;
        case betKeyword::GREEN: return rhs == Color::GREEN;
        default:                return false;
    }
}

token roll() {
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
    return token{ n, COLORS[n] };
}

int multipliers(bettype betType) {
    int payoutMult;
        switch (betType) {
        case bettype::STRAIGHT:   payoutMult = 35; break;
        case bettype::SPLIT:      payoutMult = 17; break;
        case bettype::STREET:     payoutMult = 11; break;
        case bettype::CORNERR:    payoutMult = 8;  break;
        case bettype::SIXLINE:    payoutMult = 5;  break;
        case bettype::TRIO:       payoutMult = 11; break;
        case bettype::BASKET:     payoutMult = 8;  break;
        case bettype::COLUMN:     payoutMult = 2;  break;
        case bettype::DOZEN:      payoutMult = 2;  break;
        case bettype::COLOR:      payoutMult = 1;  break;
        case bettype::PARITY:     payoutMult = 1;  break;
        case bettype::HIGHLOW:    payoutMult = 1;  break;
        default:                  payoutMult = 0;  break;
    }
    return payoutMult;
}

bool bet(bettype betType, token rollOut , betKeyword betKeyword, int betToken) {
    switch (betType) {
        case bettype::STRAIGHT: {
            if (rollOut.number == betToken) return true;
            else return false;
            break;
        }
        case bettype::SPLIT: {
            break;
        }
        case bettype::STREET: {
            break;
        }
        case bettype::CORNERR: {
            break;
        }
        case bettype::SIXLINE: {
            break;
        }
        case bettype::TRIO: {
            break;
        }
        case bettype::BASKET: {
            if (rollOut.number >= 0 && rollOut.number <= 3) return true;
            else return false;
            break;
        }
        case bettype::COLUMN: {
            if ((rollOut.number != 0) && (betToken == ((rollOut.number - 1) % 3 + 1))) return true;
            else return false;
            break;
        }
        case bettype::DOZEN: {
            if ((rollOut.number != 0) && (betToken == ((rollOut.number - 1) / 12 + 1))) return true;
            else return false;
            break;
        }
        case bettype::COLOR: {
            if (betKeyword == rollOut.color) return true;
            else return false;
            break;
        }
        case bettype::PARITY: {
            if (rollOut.number == 0) return false;
            else {
                switch(betKeyword) {
                    case betKeyword::EVEN:{
                        if (rollOut.number % 2 == 0) return true;
                        else return false;
                        break;    
                    }
                    case betKeyword::ODD: {
                        if (rollOut.number % 2 == 1) return true;
                        else return false;
                        break;
                    }
                }
            }
            break;
        }
        case bettype::HIGHLOW: {
            if (rollOut.number == 0) return false;
            else {
                switch(betKeyword) {
                    case betKeyword::HIGH:{
                        if (rollOut.number >= 19) return true;
                        else return false;
                        break;    
                    }
                    case betKeyword::LOW: {
                        if (rollOut.number <= 18) return true;
                        else return false;
                        break;
                    }
                }
            }
            break;
        }
        default: return false;
    }
    return false;
}

long long bank(bettype betType, long long balance, long long betAmmount, bool win) {
    if (win) {
        balance += betAmmount * multipliers(betType);
    } else {
        balance -= betAmmount;
    }
    return balance;
}

int main() {
    long long balance = 1000;

    bool loop = true;
    while (loop) {
        bettype betType;
        int betAmmount;
        betKeyword betKeyword;
        token rollOut = roll(); 

        std::cout << "Enter operation (betType/exit): ";
        std::cin >> betType;
        if (!std::cin) {
            std::cerr << "Invalid bet type entered!\n";
            return 1;
        }
        switch (betType) {
            case bettype::EXIT: {
                loop = false;
                continue;
            }
            case bettype::STRAIGHT: {
                int num;
                std::cout << "Enter your number and bet ammount: ";
                std::cin >> num;
                std::cin >> betAmmount; 
                bool win = bet(betType, rollOut, betKeyword, num);
                balance = bank(betType, balance, betAmmount, win);
                break;
            }
            case bettype::DOZEN:
            case bettype::COLUMN: {
                int selection;
                std::cout << "Enter your selection (1-3) and bet ammount: ";
                std::cin >> selection;
                std::cin >> betAmmount; 
                bool win = bet(betType, rollOut, betKeyword, selection);
                balance = bank(betType, balance, betAmmount, win);
                break;
            }
            case bettype::BASKET: {
                std::cout << "Enter your bet ammount: ";
                std::cin >> betAmmount; 
                bool win = bet(betType, rollOut, betKeyword, 0);
                balance = bank(betType, balance, betAmmount, win);
                break;
            }
            case bettype::COLOR: {
                std::cout << "Enter your color (RED, BLACK, GREEN) and bet ammount: ";
                std::cin >> betKeyword;
                std::cin >> betAmmount;
                bool win = bet(betType, rollOut, betKeyword, 0);
                balance = bank(betType, balance, betAmmount, win);
                break;
            }
            case bettype::PARITY: {
                std::cout << "Enter your parity (EVEN, ODD) and bet ammount: ";
                std::cin >> betKeyword;
                std::cin >> betAmmount;
                bool win = bet(betType, rollOut, betKeyword, 0);
                balance = bank(betType, balance, betAmmount, win);
                break;
            }
            case bettype::HIGHLOW: {
                std::cout << "Enter your choice (HIGH, LOW) and bet ammount: ";
                std::cin >> betKeyword;
                std::cin >> betAmmount;
                bool win = bet(betType, rollOut, betKeyword, 0);
                balance = bank(betType, balance, betAmmount, win);
                break;
            }
        }
        std::cout << "Roll outcome: " << rollOut << "\n";
        std::cout << "Current balance: " << balance << "\n";
    }

    system("pause");
    return 0;
}