#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    LL solve(int N, vector<LL> &A, vector<LL> &B) {
        LL avg = (accumulate(A.begin(), A.end(), 0LL) + accumulate(B.begin(), B.end(), 0LL))/2/N;
        LL total = 0;
        LL ra = 0, rb = 0;
        for(int i = 0; i < N; ++ i) {
            total += abs(ra + rb);
            A[i] += ra;
            B[i] += rb;
            if(A[i] >= avg && B[i] >= avg || A[i] <= avg && B[i] <= avg) {
                ra = A[i] - avg;
                rb = B[i] - avg;
            }
            else {
                if(A[i] > B[i]) {
                    LL transfer = min(A[i] - avg, avg - B[i]);
                    total += transfer;
                    ra = A[i] - transfer - avg;
                    rb = B[i] + transfer - avg;
                }
                else {
                    LL transfer = min(avg - A[i], B[i] - avg);
                    total += transfer;
                    ra = A[i] + transfer - avg;
                    rb = B[i] - transfer - avg;
                }
            }
        }
        return total;
    }
};

int main() {
    int N;
    cin >> N;
    vector<LL> A(N), B(N);
    for(int i = 0; i < N; ++ i) {
        cin >> A[i];
        cin >> B[i];
    }
    Solution s;
    cout << s.solve(N, A, B) << endl;
    return 0;
}
