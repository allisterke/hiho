#include <bits/stdc++.h>
using namespace std;

static constexpr int D = 102;
static bool exist[D][D][D];
static tuple<char, char, char> setid[D][D][D];
static stack<tuple<int, int, int>> order;
static bool valid;

class Solution {
public:
    void reset() {
        memset(exist, 0, sizeof exist);
//        memset(setid, -1, sizeof setid);
        while(order.size()) {
            order.pop();
        }
        valid = true;
    }

    vector<tuple<int, int, int>> &getValidDirections(int x, int y, int z) {
        tuple<int, int, int> dirs[] = {
                make_tuple(x-1, y, z),
                make_tuple(x+1, y, z),
                make_tuple(x, y-1, z),
                make_tuple(x, y+1, z),
                make_tuple(x, y, z-1),
                make_tuple(x, y, z+1)
        };
        static vector<tuple<int, int, int>> validDirections;
        validDirections.clear();
        for(int i = 0; i < 6; ++ i) {
            tie(x, y, z) = dirs[i];
            if(x >= 0 && x < D && y >= 0 && y < D && z > 0 && z < D) {
                validDirections.push_back(dirs[i]);
            }
        }
        return validDirections;
    };

    bool checkAdjacent(int x, int y, int z) {
        if (z != 1) {
            for (auto &d : getValidDirections(x, y, z)) {
                tie(x, y, z) = d;
                if (exist[x][y][z]) {
                    return true;
                }
            }
            return false;
        }
        else {
            return true;
        }
    }

    void addCubic(int x, int y, int z) {
        if(valid) {
            order.push(make_tuple(x, y, z));

            if (exist[x][y][z] || !checkAdjacent(x, y, z)) {
                valid = false;
            }
            else {
                exist[x][y][z] = true;
            }
        }
    }

    void setUnion(int x1, int y1, int z1, int x2, int y2, int z2) {
        tie(x1, y1, z1) = getSetid(x1, y1, z1);
        tie(x2, y2, z2) = getSetid(x2, y2, z2);
        setid[x1][y1][z1] = setid[x2][y2][z2];
    }

    tuple<int, int, int> getSetid(int x, int y, int z) {
        while(tie(x, y, z) != setid[x][y][z]) {
            tie(x, y, z) = setid[x][y][z];
        }
        return make_tuple(x, y, z);
    }

    bool checkBuildable() {
        if(!valid) {
            return false;
        }

        for(int x = D-1; x >= 0; -- x) {
            for(int y = D-1; y >= 0; -- y) {
                for(int z = D-1; z > 0; -- z) {
                    if(!exist[x][y][z]) {
                        setid[x][y][z] = make_tuple(x, y, z);
                        if (x != D - 1 && !exist[x + 1][y][z]) {
                            setUnion(x, y, z, x + 1, y, z);
                        }
                        if (y != D - 1 && !exist[x][y + 1][z]) {
                            setUnion(x, y, z, x, y + 1, z);
                        }
                        if (z != D - 1 && !exist[x][y][z + 1]) {
                            setUnion(x, y, z, x, y, z + 1);
                        }
                    }
                }
            }
        }

        while(order.size()) {
            int x, y, z;
            tie(x, y, z) = order.top();
            order.pop();

            set<tuple<int, int, int>> gs;
            for(auto &d : getValidDirections(x, y, z)) {
                int x1, y1, z1;
                tie(x1, y1, z1) = d;
                if(!exist[x1][y1][z1]) {
                    gs.insert(getSetid(x1, y1, z1));
                }
            }

            auto masterid = getSetid(D-1, D-1, D-1);
            if(gs.find(masterid) == gs.end()) {
                return false;
            }
            else {
                for(auto &g : gs) {
                    int x1, y1, z1;
                    tie(x1, y1, z1) = g;
                    setUnion(x1, y1, z1, D-1, D-1, D-1);
                }
                exist[x][y][z] = false;
                setid[x][y][z] = masterid;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    int T, N, x, y, z;
    cin >> T;
    for(int i = 0; i < T; ++ i) {
        cin >> N;
        s.reset();
        for(int j = 0; j < N; ++ j) {
            cin >> x >> y >> z;
            s.addCubic(x, y, z);
        }
        cout << (s.checkBuildable() ? "Yes" : "No") << endl;
    }
    return 0;
}
