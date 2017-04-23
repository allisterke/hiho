#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
private:
    bool check(int n, int m, vector<int> &attack, vector<int> &master, int boat, int comb, bool needBoat) {
        if(needBoat && (!(comb & boat) || __builtin_popcount(comb) > m)) {
            return false;
        }
        for(int i = 0; i < attack.size(); ++ i) {
            if(attack[i]) {
                if((comb & (1 << i)) && (comb & attack[i])) {
                    if(!(comb & master[i])) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
public:
    int solve(int n, int m, vector<int> &attack, vector<int> &master, int boat) {
        int all = (1 << n) - 1;
        if(!check(n, m, attack, master, boat, all, false)) {
            return -1;
        }
        bool visited[2][1 << n];
        memset(visited, sizeof visited, 0);
        queue<tuple<int, int, int>> q;
        q.emplace(0, all, 0);
        visited[0][all] = true;

        while(!q.empty()) {
            int side, comb, dist;
            tie(side, comb, dist) = q.front();
            q.pop();

            for(int i = comb; i; i = (i-1)&comb) {
                if(check(n, m, attack, master, boat, i, true)) {
                    int os = !side;
                    int oc = all ^ comb ^ i;
                    int od = dist + 1;
                    if(os == 1 && oc == all) {
                        return od;
                    }
                    int rc = all ^ oc;
                    if(!visited[os][oc] && check(n, m, attack, master, boat, rc, false) &&
                            check(n, m, attack, master, boat, oc, false)) {
                        visited[os][oc] = true;
                        q.emplace(os, oc, od);
                    }
                }
            }
        }

        return -1;
    }
};

int main() {
    int n, m, a, b, c;
    cin >> n >> m >> a >> b >> c;
    vector<int> attack(n), master(n);
    int boat = 0;
    for(int i = 0; i < a; ++ i) {
        int x, y;
        cin >> x >> y;
        attack[x] |= (1 << y);
    }
    for(int i = 0; i < b; ++ i) {
        int x, y;
        cin >> x >> y;
        master[y] |= (1 << x);
    }
    for(int i = 0; i < c; ++ i) {
        int x;
        cin >> x;
        boat |= (1 << x);
    }

    Solution s;
    cout << s.solve(n, m, attack, master, boat) << endl;
    return 0;
}
