#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getMinFlip(const vector<string> &board, int N, int M) {
        vector<vector<int>> dp[2] = {vector<vector<int>>(N, vector<int>(M)), vector<vector<int>>(N, vector<int>(M))};
        for(int i = 0; i < N; ++ i) {
            for(int j = 0; j < M; ++ j) {
                if(i == 0 && j == 0) {
                    int step = board[i][j] == 'b';
                    dp[0][i][j] = step;
                    if(j + 1 != M) {
                        dp[1][i][j] = step + (board[i][j+1] == '.');
                    }
                    else {
                        dp[1][i][j] = step;
                    }
                }
                else if(i == 0) {
                    int step = dp[0][i][j-1] + (board[i][j] == 'b');
                    dp[0][i][j] = step;
                    if(j + 1 != M) {
                        dp[1][i][j] = step + (board[i][j+1] == '.');
                    }
                    else {
                        dp[1][i][j] = step;
                    }
                }
                else if(j == 0) {
                    int step = dp[1][i-1][j] + (board[i][j] == 'b');
                    dp[1][i][j] = step;
                    if(i + 1 != N) {
                        dp[0][i][j] = step + (board[i+1][j] == '.');
                    }
                    else {
                        dp[0][i][j] = step;
                    }
                }
                else {
                    if(i + 1 == N && j + 1 == M) {
                        dp[0][i][j] = dp[1][i][j] = min(dp[0][i][j-1], dp[1][i-1][j]) + (board[i][j] == 'b');
                    }
                    else {
                        int right = dp[0][i][j-1] + (board[i][j] == 'b');
                        int down = dp[1][i-1][j] + (board[i][j] == 'b');

                        if(i + 1 != N && j + 1 != M) {
                            dp[0][i][j] = min(right, down + (board[i+1][j] == '.'));
                            dp[1][i][j] = min(down, right + (board[i][j+1] == '.'));
                        }
                        else if(i + 1 == N) {
                            dp[0][i][j] = min(right, down);
                            dp[1][i][j] = min(down, right + (board[i][j+1] == '.'));
                        }
                        else { // j + 1 == M
                            dp[0][i][j] = min(right, down + (board[i+1][j] == '.'));
                            dp[1][i][j] = min(down, right);
                        }
                    }
                }
            }
        }
        return min(dp[0].back().back(), dp[1].back().back());
    }
};

int main() {
    int N, M;
    vector<string> board;
    Solution s;
    cin >> N >> M;
    board.resize(N);
    for(int i = 0; i < N; ++ i) {
        cin >> board[i];
    }
    cout << s.getMinFlip(board, N, M) << endl;
}