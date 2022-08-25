#include <iostream>

void solve() {
    int n;
    std::cin >> n;

    int sum = 0;
    bool even = true;
    while (n--) {
        int x;
        std::cin >> x;

        sum ^= x;
        if (x % 2 != 0) even = false;
    }

    std::cout << (sum == 1 || (sum == 0 && even) ? "Bob" : "Alice") << "\n";
}
