#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    double solve(vector<double> &p, int M) {
        vector<vector<double>> dp(p.size()+1, vector<double>(p.size()+1));
        for(int i = 0; i <= p.size(); ++ i) {
            for(int j = 0; j <= i; ++ j) {
                if(i == 0 && j == 0) {
                    dp[i][j] = 1;
                }
                else if(j == 0) {
                    dp[i][j] = dp[i-1][j] * (1. - p[i-1]);
                }
                else {
                    dp[i][j] = p[i-1] * dp[i-1][j-1] + (1. - p[i-1]) * dp[i-1][j];
                }
            }
        }
        return dp.back()[M];
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    vector<double> p(N);
    for(auto &q : p) {
        cin >> q;
    }
    Solution s;
    cout << s.solve(p, M) << endl;
    return 0;
}
