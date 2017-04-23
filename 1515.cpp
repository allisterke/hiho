#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:

};

pair<int, LL> pivot(vector<pair<int, LL>> &students, int x) {
    if(students[x].first != x) {
        auto p = pivot(students, students[x].first);
        students[x].first = p.first;
        students[x].second += p.second;
    }
    return students[x];
}

void join(vector<pair<int, LL>> &students, int x, int y, LL s) {
    auto p1 = pivot(students, x);
    auto p2 = pivot(students, y);
    students[p2.first].first = p1.first;
    students[p2.first].second = p1.second - p2.second - s;
}

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<pair<int, LL>> students(N+1);
    for(int i = 1; i <= N; ++ i) {
        students[i] = make_pair(i, 0LL);
    }
    for(int i = 0; i < M; ++ i) {
        int x, y, s;
        cin >> x >> y >> s;
        join(students, x, y, s);
    }
    for(int i = 0; i < Q; ++ i) {
        int x, y;
        cin >> x >> y;
        auto p1 = pivot(students, x);
        auto p2 = pivot(students, y);
        cout << (p1.first != p2.first ? -1 : p1.second - p2.second) << endl;

    }
    Solution s;
    return 0;
}
