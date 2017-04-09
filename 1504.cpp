#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;

class Solution {
public:
    int solve(int N, int R, int C) {
        vector<vector<LL>> matrix(64, vector<LL>(64));
        for(int x = 0; x < 8; ++ x) {
            for (int y = 0; y < 8; ++y) {
                int p[8][2] = {
                        {x - 1, y - 2},
                        {x + 1, y - 2},
                        {x - 2, y - 1},
                        {x + 2, y - 1},
                        {x - 1, y + 2},
                        {x + 1, y + 2},
                        {x - 2, y + 1},
                        {x + 2, y + 1},
                };
                for (int k = 0; k < 8; ++k) {
                    if (p[k][0] >= 0 && p[k][0] < 8 && p[k][1] >= 0 && p[k][1] < 8) {
                        matrix[p[k][0] * 8 + p[k][1]][x * 8 + y] = 1;
                    }
                }
            }
        }

        unordered_map<int, vector<vector<LL>>> cache;
        auto result = power(matrix, N, cache);

        vector<LL> init(64);
        init[R * 8 + C] = 1;
        vector<LL> finish(64);
        for(int i = 0; i < 64; ++ i) {
            for(int j = 0; j < 64; ++ j) {
                finish[i] += init[j] * result[j][i];
                finish[i] %= MOD;
            }
        }

        LL total = accumulate(finish.begin(), finish.end(), 0LL);
        return total %= MOD;
    }

    vector<vector<LL>> &power(const vector<vector<LL>> &m, int N,
                             unordered_map<int, vector<vector<LL>>> &cache) {
        if(cache.find(N) == cache.end()) {
            if (N > 1) {
                cache[N] = (N % 2 == 0) ? mul(power(m, N / 2, cache), power(m, N / 2, cache))
                                        : mul(mul(power(m, N / 2, cache), power(m, N / 2, cache)), m);
            }
            else {
                cache[N] = m;
            }
        }
        return cache[N];
    }

    vector<vector<LL>> mul(const vector<vector<LL>> &m1, const vector<vector<LL>> &m2) {
        vector<vector<LL>> result(64, vector<LL>(64));
        for(int i = 0; i < 64; ++ i) {
            for(int j = 0; j < 64; ++ j) {
                for(int k = 0; k < 64; ++ k) {
                    result[i][j] += m1[i][k] * m2[k][j];
                    result[i][j] %= MOD;
                }
            }
        }
        return result;
    }


    int solve0(int N, int R, int C) {
        vector<vector<vector<LL>>> dp(N+1, vector<vector<LL>>(8, vector<LL>(8)));
        dp[0][R][C] = 1;
        for(int i = 1; i <= N; ++ i) {
            for(int x = 0; x < 8; ++ x) {
                for(int y = 0; y < 8; ++ y) {
                    int p[8][2] = {
                            {x-1, y-2}, {x+1, y-2}, {x-2, y-1}, {x+2, y-1},
                            {x-1, y+2}, {x+1, y+2}, {x-2, y+1}, {x+2, y+1},
                    };
                    for(int k = 0; k < 8; ++ k) {
                        if(p[k][0] >= 0 && p[k][0] < 8 && p[k][1] >= 0 && p[k][1] < 8) {
                            dp[i][x][y] += dp[i-1][p[k][0]][p[k][1]];
                            dp[i][x][y] %= MOD;
                        }
                    }
                }
            }
        }

        LL total = 0;
        for(int i = 0; i < 8; ++ i) {
            for(int j = 0; j < 8; ++ j) {
                total += dp.back()[i][j];
                total %= MOD;
            }
        }
        return total;
    }
};

int main() {
    Solution s;
    int N, R, C;
    while(cin >> N >> R >> C) {
        cout << s.solve(N, R - 1, C - 1) << endl;
    }
    return 0;
}
