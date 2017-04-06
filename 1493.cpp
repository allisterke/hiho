#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool testPrime(int n) {
        for(int i = 2; i*i <= n; ++ i) {
            if(n % i == 0) {
                return false;
            }
        }
        return true;
    }
    pair<int, int> solve(int n) {
        for(int i = 2; i*2 <= n; ++ i) {
            if(testPrime(i) && testPrime(n-i)) {
                return make_pair(i, n-i);
            }
        }
        return make_pair(0, 0);
    }
};

int main() {
    int N;
    Solution s;
    while(cin >> N) {
        auto r = s.solve(N);
        cout << r.first << ' ' << r.second << endl;
    }
    return 0;
}
