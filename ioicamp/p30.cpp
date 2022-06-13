#include <iostream>
#define Print(x) std::cout << #x << "!" << std::endl;

int main() {
    std::string welcome = "WELCOME";
    Print(welcome);
    return 0;
}

