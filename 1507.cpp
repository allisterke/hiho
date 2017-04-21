#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:

};

inline bool rootable(vector<int> &parents, int child, int parent) {
    parents[child] = parent;
    int node = parent;
    for(; node != 1 && node != child; node = parents[node]);
    return node == 1;
}

int main() {
    int N;
    cin >> N;
    vector<int> parents(N+1);
    vector<int> lineNum(N+1);
    tuple<int, int, int> twoParents;
    for(int i = 1; i <= N; ++ i) {
        int parent, child;
        cin >> parent >> child;
        if(parents[child]) {
            twoParents = make_tuple(child, parent, i);
        }
        else {
            parents[child] = parent;
            lineNum[child] = i;
        }
    }

    if(parents[1]) {
        cout << lineNum[1] << endl;
    }
    else {
        int c, p, l;
        tie(c, p, l) = twoParents;
        auto r1 = rootable(parents, c, parents[c]);
        auto r2 = rootable(parents, c, p);
        if(r1 && r2) {
            cout << lineNum[c] << ' ' << l << endl;
        }
        else {
            cout << (r1 ? l : lineNum[c]) << endl;
        }
    }

    Solution s;
    return 0;
}
