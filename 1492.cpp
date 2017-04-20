#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
constexpr LL MOD = 1e9 + 7;

class Solution {
public:
    pair<int, LL> solve(const string &line) {
        auto left = solveLeft(line);

        string tmp(line.rbegin(), line.rend());
        for_each(tmp.begin(), tmp.end(), [=](char &c) { c = c == '(' ? ')' : '('; });
        auto right = solveLeft(tmp);

        return make_pair(left.first + right.first, left.second * right.second % MOD);
    }

    pair<int, LL> solveLeft(const string &line) {
        stack<char> prs;
        stack<int> pos;
        for(int i = 0; i < line.size(); ++ i) {
            char c = line[i];
            if(prs.empty() || c == '(' || c == ')' && prs.top() != '(') {
                prs.push(c);
                pos.push(i);
            }
            else {
                prs.pop();
                pos.pop();
            }
        }

        while(!prs.empty() && prs.top() == '(') {
            prs.pop();
            pos.pop();
        }

        return prs.empty() ? make_pair(0, 1LL) :
               make_pair((int)prs.size(), countVariations(string(line.begin(), line.begin() + pos.top() + 1), prs.size()));
    }

    LL countVariations(const string &line, int insertCount) {
        string str(line);
        reverse(str.begin(), str.end());
        for(auto &c : str) {
            c = c == '(' ? ')' : '(';
        }

        vector<int> insert;
        int left = 0, right = 0;
        for(int i = 0; i < str.size(); ) {
            ++ left;
            int j = i+1;
            for(; j < str.size() && str[j] == ')'; ++ j, ++ right);
            i = j;
            insert.push_back(min(left - right, insertCount));
        }

        vector<vector<LL>> dp(insert.size(), vector<LL>(insertCount+1));
        for(int i = 0; i < dp.size(); ++ i) {
            for(int j = 0; j <= insert[i]; ++ j) {
                if(i == 0) {
                    dp[i][j] = 1;
                }
                else {
                    for(int k = 0; k <= j; ++ k) {
                        dp[i][j] += dp[i-1][j - k];
                    }
                    dp[i][j] %= MOD;
                }
            }
        }
        return dp.back()[insertCount];
    }
};

int main() {
    Solution s;
//    cout << s.getChoices(200, 400) << endl;
    string line;
    while(cin >> line) {
        auto r = s.solve(line);
        cout << r.first << ' ' << r.second << endl;
    }
    return 0;
}
