#include <iostream>
#include <vector>

std::vector<int> arr;
int fibonacci(int i) {
    if (i <= 1) return 1;
    arr.push_back(0);
    int sz = arr.size(), &a = arr[sz-1];
    a = fibonacci(i-1) + fibonacci(i-2);
    return arr[sz-1];
}

int main() {
    int k;
    std::cin >> k;
    std::cout << fibonacci(k) << '\n';
}

