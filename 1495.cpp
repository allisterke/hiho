#include <bits/stdc++.h>
using namespace std;

tuple<int, int, int> ss[100][100][4];

class Solution {
public:
    tuple<int, int, int> getSetId(int x, int y, int z) {
        if(tie(x, y, z) != ss[x][y][z]) {
            ss[x][y][z] = getSetId(get<0>(ss[x][y][z]),
                                get<1>(ss[x][y][z]),
                                get<2>(ss[x][y][z]));
        }
        return ss[x][y][z];
    }

    void unionSets(int x1, int y1, int z1, int x2, int y2, int z2) {
        auto s1 = getSetId(x1, y1, z1);
        auto s2 = getSetId(x2, y2, z2);
        if(s1 != s2) {
            ss[get<0>(s1)][get<1>(s1)][get<2>(s1)] = s2;
        }
    }
    int solve(int n, int m, vector<string> &board) {
        for(int i = 0; i < n; ++ i) {
            for(int j = 0; j < m; ++ j) {
                for(int k = 0; k < 4; ++ k) {
                    ss[i][j][k] = make_tuple(i, j, k);
                }
                if(i != 0) {
                    unionSets(i, j, 1, i-1, j, 3);
                }
                if(j != 0) {
                    unionSets(i, j, 0, i, j-1, 2);
                }
                switch(board[i][j]) {
                    case '/':
                        unionSets(i, j, 0, i, j, 1);
                        unionSets(i, j, 2, i, j, 3);
                        break;
                    case '\\':
                        unionSets(i, j, 1, i, j, 2);
                        unionSets(i, j, 0, i, j, 3);
                        break;
                    default:
                        unionSets(i, j, 0, i, j, 1);
                        unionSets(i, j, 2, i, j, 1);
                        unionSets(i, j, 2, i, j, 3);
                }
            }
        }

        set<tuple<int, int, int>> ids;
        for(int i = 0; i < n; ++ i) {
            for(int j = 0; j < m; ++ j) {
                for(int k = 0; k < 4; ++ k) {
                    ids.insert(getSetId(i, j, k));
                }
            }
        }

        return ids.size();
    }
};

int main() {
    Solution s;
    int N, M;
    cin >> N >> M;
    vector<string> board(N);
    cin.ignore();
    for(int i = 0; i < N; ++ i) {
        getline(cin, board[i]);
    }
    cout << s.solve(N, M, board) << endl;
    return 0;
}
