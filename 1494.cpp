#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    unordered_map<int, int> edges;
    int levels;
public:
    void clear() {
        levels = 0;
        edges.clear();
    }

    void addBricks(vector<int> &bricks) {
        ++ levels;
        int offset = 0;
        for(int i = 0; i+1 < bricks.size(); ++ i) {
            offset += bricks[i];
            ++ edges[offset];
        }
    }

    int bestPos() {
        int maxd = 0;
        for(auto it = edges.begin(); it != edges.end(); ++ it) {
            maxd = max(maxd, it->second);
        }
        return levels - maxd;
    }
};

int main() {
    Solution s;
    int N, C;
    vector<int> bricks;
    cin >> N;
    s.clear();
    for(int i = 0; i < N; ++ i) {
        cin >> C;
        bricks.resize(C);
        for(int j = 0; j < C; ++ j) {
            cin >> bricks[j];
        }
        s.addBricks(bricks);
    }
    cout << s.bestPos() << endl;
    return 0;
}
