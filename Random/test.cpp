#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <ranges>
#include <numeric>
struct cmp {
    bool operator()(const std::pair<int, long long> &a, 
        const std::pair<int, long long> &b) {
        return a.first > b.first;
    }
};
int main() {
    int N;
    std::cin >> N;
    std::vector<int> A(N), D(N);
    for (int i = 0; i < N; i++) { std::cin >> A[i]; std::cout << A[i] << "\n"; }
    std::cout << "\n" << N << "\n";
    for (int i = 0; i < N; i++) { std::cin >> D[i]; std::cout << i << " " << D[i] << "\n"; }
    std::cout << __LINE__ << "\n";
    std::vector<std::vector<std::pair<int, long long>>> pushed(N);

    for (int i = 0; i < N; i++) { 
        pushed[std::max(0, i - D[i])].emplace_back(i + D[i], A[i]);
    }
    auto test = [&](long long Z) {
        std::cout << Z << "\n";
        std::priority_queue<std::pair<int, long long>,
            std::vector<std::pair<int, long long>>, 
            cmp> shift;
        for (int i = 0; i < N; i++) {
            for (auto j : pushed[i]) { shift.push(j); }
            long long left = Z;
            if (shift.size() > 0 && shift.top().first < i) { return false; }
            while (shift.size() > 0 && left >= shift.top().second) {
                left -= shift.top().second;
                shift.pop();
            }
            if (left > 0) {
                auto tmp = shift.top();
                shift.pop();
                shift.emplace(tmp.first, tmp.second - left);
            }
        }
        return shift.empty();
    };
    // std::cout << *std::ranges::partition_point(
    //     std::views::iota(0LL, 200000000000001LL),
    //     test) - 1 << "\n";
    // long long lo = 0, hi = 200000000000000LL;
    // while (lo < hi) {
    //     long long mid = std::midpoint(lo, hi);
    //     if (test(mid)) hi = mid;
    //     else lo = mid + 1;
    // }
    // std::cout << lo << "\n";
    //bool b = test(7LL);
    //std::cout << b << "\n";
}