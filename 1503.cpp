#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    inline int pairCount(vector<int> &count) {
        int pc = 0;
        for(auto c : count) {
            pc += c / 2;
        }
        return pc;
    }

    inline bool checkPair(vector<int> &c1, vector<int> &c2) {
        return pairCount(c1) + pairCount(c2) >= 7;
    }

    int checkSequenceCount(vector<int> &count, int start) {
        if(start >= 9) {
            return 0;
        }
        if(start > 6) {
            return (count[start] >= 3) + checkSequenceCount(count, start + 1);
        }
        else {
            int maxs = 0;
            if(count[start] >= 3) { // get one sequence
                count[start] -= 3;
                maxs = 1 + checkSequenceCount(count, start);
                count[start] += 3;
            }

            if(maxs >= 4) {
                return maxs;
            }

            if(count[start] && count[start+1] && count[start+2]) { // get one sequence
                for(int j = 0; j < 3; ++ j) {
                    count[start + j] -= 1;
                }
                maxs = max(maxs, 1 + checkSequenceCount(count, start));
                for(int j = 0; j < 3; ++ j) {
                    count[start + j] += 1;
                }
            }

            if(maxs >= 4) {
                return maxs;
            }

            maxs = max(maxs, checkSequenceCount(count, start+1)); // ignore this one
            return maxs;
        }
    }

    bool check(vector<int> &c1, vector<int> &c2) {
        if(checkPair(c1, c2)) {
            return true;
        }
        for(int i = 0; i < c1.size(); ++ i) {
            if(c1[i] >= 2) {
                c1[i] -= 2;
                bool success = checkSequenceCount(c1, 0) + checkSequenceCount(c2, 0) >= 4;
                c1[i] += 2;
                if(success) {
                    return true;
                }
            }
        }
        for(int i = 0; i < c2.size(); ++ i) {
            if(c2[i] >= 2) {
                c2[i] -= 2;
                bool success = checkSequenceCount(c1, 0) + checkSequenceCount(c2, 0) >= 4;
                c2[i] += 2;
                if(success) {
                    return true;
                }
            }
        }
        return false;
    }

    bool check(vector<int> count[]) {
        return check(count[0], count[1]) || check(count[1], count[2]) || check(count[0], count[2]);
    }
public:
    int solve(vector<string> &tile) {
        vector<int> count[] = { vector<int>(9), vector<int>(9), vector<int>(9) };
        for(auto &t : tile) {
            ++ count[t[0] - 'a'][t[1] - '1'];
        }
        bool hu = false;
        while(tile.size() >= 14 && check(count)) {
            hu = true;

            auto &t = tile.back();
            -- count[t[0] - 'a'][t[1] - '1'];
            tile.pop_back();
        }
        return hu ? tile.size() - 13 : -1;
    }
};

int main() {
    Solution s;
    int N;
    cin >> N;
    vector<string> tile(14 + N);
    for(int i = 0; i < tile.size(); ++ i) {
        cin >> tile[i];
    }
    cout << s.solve(tile) << endl;
    return 0;
}
