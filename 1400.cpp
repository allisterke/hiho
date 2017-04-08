#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool mark[26*26];
    void addIllegal(char a, char b) {
        mark[(a - 'a') * 26 + (b - 'a')] = true;
        mark[(b - 'a') * 26 + (a - 'a')] = true;
    }
    bool isLegal(char a, char b) {
        return !mark[(a - 'a') * 26 + (b - 'a')];
    }
public:
    Solution() : mark{} {}
    void addIllegal(const string &illegal) {
        if(illegal.size() == 2) {
            addIllegal(illegal[0], illegal[1]);
        }
    }

    int solve(const string &composition) {
        vector<int> keep(composition.size());
        vector<int> remove(composition.size());

        vector<int> position(26, -1); // character a-z position cache
        for(int i = 0; i < composition.size(); ++ i) {
            if(i == 0) {
                keep[i] = 0;
                remove[i] = 1;
            }
            else {
                remove[i] = min(keep[i-1], remove[i-1]) + 1;

                keep[i] = i; // initialize to remove all others
                for(int j = 0; j < position.size(); ++ j) {
                    if(position[j] >= 0 && isLegal(j + 'a', composition[i])) {
                        keep[i] = min(keep[i], keep[position[j]] + i - 1- position[j]);
                    }
                }
            }
            position[composition[i] - 'a'] = i;
        }
        return min(keep.back(), remove.back());
    }
};

int main() {
    Solution s;
    int N, M;
    string composition;
    string illegal;
    cin >> N;
    cin >> composition;
    cin >> M;
    for(int i = 0; i < M; ++ i) {
        cin >> illegal;
        s.addIllegal(illegal);
    }
    cout << s.solve(composition) << endl;

    return 0;
}
