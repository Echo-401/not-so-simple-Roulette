#include <lib.hpp>

enum class Color { RED, BLACK, GREEN };
enum class bettype {STRAIGHT, SPLIT, STREET, CORNERR, SIXLINE, TRIO, BASKET, COLUMN, DOZEN, COLOR, PARITY, HIGHLOW}; //type of bet
//                                                            Inside bets  |  Outside bets
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
    else in.setstate(std::ios::failbit); // mark as invalid

    return in;
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

long long betCalc(long long betAmmount, bettype betType) {
    long long payoutMult;
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
    return betAmmount * payoutMult;
}

long long balance(bool winCon , long long currentBalance, long long betAmmount, bettype betType, spin rollOut) {
    long long newBalance ;
    if (winCon) {
        newBalance = currentBalance + betCalc(betAmmount, betType);
        std::cout << "You won! " << rollOut << "\n";
    } else {
        newBalance = currentBalance - betAmmount;
        std::cout << "You lost! " << rollOut << "\n";
    }
    std::cout << "New balance: " << newBalance << "\n";
    return newBalance;
}

void betHandle(long long& currentBalance, long long betAmmount, bettype betType, spin rollOut) {
    if (betAmmount > currentBalance) {
        std::cerr << "Insufficient balance for this bet!\n";
        return;
    } else if (betAmmount <= 0) {
        std::cerr << "Bet amount must be positive!\n";
        return;
    } else {
        switch (betType) {
            case bettype::STRAIGHT:
                int num;
                std::cin >> num;
                std::cin >> betAmmount; 
                if(rollOut.number == num) currentBalance = balance(true, currentBalance, betAmmount, betType, rollOut);
                else currentBalance = balance(false, currentBalance, betAmmount, betType, rollOut);
                break;
            case bettype::SPLIT:
                break;
            case bettype::STREET:
                break;
            case bettype::CORNERR:
                break;
            case bettype::SIXLINE:
                break;
            case bettype::TRIO:
                break;
            case bettype::BASKET:
                break;
            case bettype::COLUMN:
                break;
            case bettype::DOZEN:
                break;
            case bettype::COLOR:
                break;
            case bettype::PARITY:
                break;
            case bettype::HIGHLOW:

                break;

        }
    }
        
}

int main() {
    long long currentBalance = 1000;
    int betAmmount;
    bettype betType;

    std::cout << "Enter your bet (type amount): ";
    std::cin >> betType;
    if (!std::cin) {
    std::cerr << "Invalid bet type entered!\n";
    return 1;
    }  
    spin rollOut = roll();

    switch (betType) {
        case bettype::STRAIGHT:
            int num;
            std::cin >> num;
            std::cin >> betAmmount; 
            if(rollOut.number == num) currentBalance = balance(true, currentBalance, betAmmount, betType, rollOut);
            else currentBalance = balance(false, currentBalance, betAmmount, betType, rollOut);
            break;
        case bettype::SPLIT:
            break;
        case bettype::STREET:
            break;
        case bettype::CORNERR:
            break;
        case bettype::SIXLINE:
            break;
        case bettype::TRIO:
            break;
        case bettype::BASKET:
            break;
        case bettype::COLUMN:
            break;
        case bettype::DOZEN:
            break;
        case bettype::COLOR:
            break;
        case bettype::PARITY:
            break;
        case bettype::HIGHLOW:

            break;

    }
    "straight 25 500"
    "color red 250"
    "highlow low 300"
    "split 7-10 100"
    "basket 750"
    "dozen 2 400"
    "collumn 3 600"
    "Trio 2-3 200"// 0-2-3
    "street 4-5-6 150"
    "corner 1-2-4-5 100"
    "parity even 350"    ;

    system("pause");
    return 0;
}
