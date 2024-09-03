#include <iostream>
#include <vector>
 
int main() {
    int n;
    std::cin >> n;
 
    std::vector<int> a(n, 0);
 
    int max = -2147483648, min = 2147483647;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        max = std::max(max, a[i]);
        min = std::min(min, a[i]);
    }
 
    std::vector<int> elems(max - min + 1, -1);
    std::vector<long long int> dp(n + 1, 0);
    dp[0] = 1;
 
    for (int i = 1; i <= n; ++i) {
        dp[i] = 2 * dp[i - 1] % 1000000007;
 
        if (elems[a[i - 1] - min] != -1) {
            dp[i] = (dp[i] - dp[elems[a[i - 1] - min]] + 1000000007) % 1000000007;
        }
 
        elems[a[i - 1] - min] = i - 1;
    }
 
    std::cout << dp[n] - 1;
 
    return 0;
}