#include "../sort-char.h"
#include <iostream>

int main() {
    char v[1001];
    std::cin >> v;
    sort_char(v);
    std::cout << v << std::endl;
    return 0;
}
