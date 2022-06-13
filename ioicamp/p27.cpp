#include <valarray>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>

struct my_array {
    int arr[10];
    void init() {
        for (int i = 0;i < 10;++i)
            std::cin >> arr[i];
    }
    my_array() {
        for (int i = 0;i < 10;++i)
            arr[i] = i * i;
    }
};
std::valarray<my_array> item(2);

my_array &get_index(int id) {
    return item[id];
};

int main() {
    my_array a;
    a.init();
    item[0] = a;
    auto vec1 = get_index(0).arr;

    my_array b;
    item[1] = b;
    auto vec2 = get_index(1).arr;

    for (int i = 0;i < 10;++i)
        std::cout << vec1[i] + vec2[i] << '\n';
}
