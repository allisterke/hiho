#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    int solve(int N, int M, int K, const vector<vector<LL>> &matrix) {
        int maxe = 0;
        for(int i = 0; i < M; ++ i) {
            vector<LL> sum(N);
            for(int j = i; j < M; ++ j) {
                for(int k = 0; k < N; ++ k) {
                    sum[k] += matrix[k][j];
                }
                int p = 0, q = 0;
                LL tsum = 0;
                while(p < N) {
                    tsum += sum[p ++];
                    while(tsum > K) {
                        tsum -= sum[q ++];
                    }
                    maxe = max(maxe, (p - q) * (j - i + 1));
                }
            }
        }
        return maxe;
    }
};

int main() {
    Solution s;
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<LL>> matrix(N, vector<LL>(M));
    for(int i = 0; i < N; ++ i) {
        for(int j = 0; j < M; ++ j) {
            cin >> matrix[i][j];
        }
    }
    cout << s.solve(N, M, K, matrix) << endl;
    return 0;
}
