#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> solve(int N, int M, int K, vector<vector<int>> &levels,
                      vector<int> &leaves,
                      vector<vector<int>> &matrix) {
        vector<int> parent(N+1);
        vector<int> leafMap(N+1);
        for(auto leaf : leaves) {
            leafMap[leaf] = true;
        }

        vector<vector<int>> dist(N+1, vector<int>(N+1)); // copy leaf distances to global matrix
        for(int i = 0; i < leaves.size(); ++ i) {
            for(int j = 0; j < leaves.size(); ++ j) {
                dist[leaves[i]][leaves[j]] = matrix[i][j];
                dist[leaves[j]][leaves[i]] = matrix[j][i];
            }
        }

        for(int i = levels.size() - 1; i > 0; -- i) {
            int k = 0;
            for(; leafMap[levels[i-1][k]]; ++ k); // find first non-leaf node in the parent node level
            for(int j = 0; j < levels[i].size(); ++ j) {
                if(j == 0) {
                    parent[levels[i][0]] = levels[i - 1][k];
                }
                else {
                    if (dist[levels[i][j]][levels[i][j - 1]] == 2) {
                        // do nothing;
                    }
                    else {
                        for (++k; leafMap[levels[i - 1][k]]; ++k); // find next non-leaf node in the parent node level
                    }

                    parent[levels[i][j]] = levels[i - 1][k];

                    // update distance between parent nodes
                    dist[parent[levels[i][j]]][parent[levels[i][j - 1]]] = dist[levels[i][j]][levels[i][j - 1]] - 2;
                    dist[parent[levels[i][j - 1]]][parent[levels[i][j]]] = dist[levels[i][j - 1]][levels[i][j]] - 2;
                }

                for(int level = 1; level < i; ++ level) {
                    for (int a = 0; a < levels[level].size(); ++a) { // update distance between leaf & parent node
                        if (leafMap[levels[level][a]]) {
                            dist[parent[levels[i][j]]][levels[level][a]] = dist[levels[i][j]][levels[level][a]] - 1;
                            dist[levels[level][a]][parent[levels[i][j]]] = dist[levels[level][a]][levels[i][j]] - 1;
                        }
                    }
                }
            }
        }

        return parent;
    }
};

int main() {
    Solution s;
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> levels(M);
    for(int i = 0; i < M; ++ i) {
        int A;
        cin >> A;
        levels[i].resize(A);
    }
    for(int i = 0; i < M; ++ i) {
        for(int j = 0; j < levels[i].size(); ++ j) {
            cin >> levels[i][j];
        }
    }
    vector<int> leaves(K);
    for(int i = 0; i < K; ++ i) {
        cin >> leaves[i];
    }
    vector<vector<int>> matrix(K, vector<int>(K));
    for(int i = 0; i < K; ++ i) {
        for(int j = 0; j < K; ++ j) {
            cin >> matrix[i][j];
        }
    }

    auto parents = s.solve(N, M, K, levels, leaves, matrix);
    for(int i = 1; i < parents.size(); ++ i) {
        if(i > 1) {
            cout << ' ';
        }
        cout << parents[i];
    }
    cout << endl;
    return 0;
}
