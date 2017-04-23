#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
private:
    LL solveOrdered(vector<LL> &A, vector<LL> &B, vector<LL> &C) {
        LL mind = numeric_limits<LL>::max();
        for(auto a : A) {
            auto it1 = lower_bound(B.begin(), B.end(), a);
            if(it1 != B.end()) {
                auto b = *it1;
                auto it2 = lower_bound(C.begin(), C.end(), b);
                if(it2 != C.end()) {
                    auto c = *it2;
                    mind = min(mind, (c - a) << 1);
                }
            }
        }
        return mind;
    }
public:
    LL solve(vector<LL> &A, vector<LL> &B, vector<LL> &C) {
        vector<LL>* abc[] = {&A, &B, &C};
        for(int i = 0; i < sizeof abc / sizeof abc[0]; ++ i) {
            sort(begin(*abc[i]), end(*abc[i]));
        }

        vector<int> perm{0, 1, 2};
        LL mind = numeric_limits<LL>::max();
        while (true) {
            mind = min(mind, solveOrdered(*abc[perm[0]], *abc[perm[1]], *abc[perm[2]]));
            if(!next_permutation(perm.begin(), perm.end())) {
                break;
            }
        }

        return mind;
    }
};

int main() {
    int N, M, L;
    cin >> N >> M >> L;
    vector<LL> A(N), B(M), C(L);
    for(auto &a : A) {
        cin >> a;
    }
    for(auto &b : B) {
        cin >> b;
    }
    for(auto &c : C) {
        cin >> c;
    }
    Solution s;
    cout << s.solve(A, B, C) << endl;
    return 0;
}
