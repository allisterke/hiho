#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double solve(int P, int Q, int N) {
        vector<double> expect(N+1);
        for(int i = 1; i <= N; ++ i) {
            double e1 = 0.;
            double p = 1.;
            for(int j = 0; j <= ((100-P)%Q == 0 ? (100-P)/Q : (100-P)/Q+1); ++ j) {
                e1 += p * min(P + j*Q, 100) / 100. * (j + 1);
                p *= (100 - min(P + j*Q, 100))/100.;
            }
            expect[i] = expect[i-1] + e1;
            P /= 2;
        }
        return expect.back();
    }
};

int main() {
    Solution s;
    int P, Q, N;
    cin >> P >> Q >> N;
    printf("%.2lf\n", s.solve(P, Q, N));
    return 0;
}
