#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    LL solve(vector<pair<LL, LL>> &queens) {
        LL total = 0;
        unordered_map<LL, LL> count;
        for(auto &queue : queens) {
            ++ count[queue.first];
        }
        for(auto &kv : count) {
            if(kv.second > 1) {
                total += kv.second * (kv.second - 1) / 2;
            }
        }

        count.clear();
        for(auto &queue : queens) {
            ++ count[queue.second];
        }
        for(auto &kv : count) {
            if(kv.second > 1) {
                total += kv.second * (kv.second - 1) / 2;
            }
        }

        count.clear();
        for(auto &queue : queens) {
            ++ count[queue.second - queue.first];
        }
        for(auto &kv : count) {
            if(kv.second > 1) {
                total += kv.second * (kv.second - 1) / 2;
            }
        }

        LL minx = numeric_limits<int>::max(), maxy = numeric_limits<int>::min();
        for(int i = 0; i < queens.size(); ++ i) {
            minx = min(minx, queens[i].first);
            maxy = max(maxy, queens[i].second);
        }

        for(int i = 0; i < queens.size(); ++ i) {
            queens[i].first -= minx;
            queens[i].second = maxy - queens[i].second;
        }

        count.clear();
        for(auto &queue : queens) {
            ++ count[queue.second - queue.first];
        }
        for(auto &kv : count) {
            if(kv.second > 1) {
                total += kv.second * (kv.second - 1) / 2;
            }
        }

        return total;
    }
};

int main() {
    Solution s;
    int N;
    cin >> N;
    vector<pair<LL, LL>> queens(N);
    for(int i = 0; i < N; ++ i) {
        cin >> queens[i].first >> queens[i].second;
    }
    cout << s.solve(queens);
    return 0;
}
