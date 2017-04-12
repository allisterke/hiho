#include <bits/stdc++.h>
using namespace std;

using Member = tuple<int, int, int, int, bool>; // information, contribution, cost, minCost, killable

class Solution {
private:
    bool checkKillable(vector<vector<int>> &subordinates, vector<Member> &members, int root) {
        bool killable = false;
        if(subordinates[root].empty()) {
            killable = true;
        }
        else {
            int contribution = 0;
            for(auto sub : subordinates[root]) {
                if(checkKillable(subordinates, members, sub)) {
                    contribution += get<1>(members[sub]);
                }
            }
            if(contribution >= get<0>(members[root])) {
                killable = true;
            }
        }
        get<4>(members[root]) = killable;
        return killable;
    }

    void checkMinimumCost(vector<vector<int>> &subordinates, vector<Member> &members, int root) {
        if(subordinates[root].empty()) {
            get<3>(members[root]) = get<2>(members[root]);
            return ;
        }
        for(auto sub : subordinates[root]) {
            checkMinimumCost(subordinates, members, sub);
        }
        map<int, int> cc;
        cc.emplace(0, 0);
        for(auto sub : subordinates[root]) {
            if(get<4>(members[sub])) {
                map<int, int> tmp = cc;
                for(auto &kv : cc) {
                    int contribution = kv.first + get<1>(members[sub]);
                    int cost = kv.second + get<3>(members[sub]);
                    if(tmp.find(contribution) == tmp.end()) {
                        tmp[contribution] = cost;
                    }
                    else if(cost < tmp[contribution]){
                        tmp[contribution] = cost;
                    }
                }
                cc = move(tmp);
            }
        }
        for(auto it = cc.lower_bound(get<0>(members[root])); it != cc.end(); ++ it) {
            get<3>(members[root]) = min(get<3>(members[root]), it->second + get<2>(members[root]));
        }
    }
public:
    int solve(vector<vector<int>> &subordinates, vector<Member> &members, int root) {
        if(!checkKillable(subordinates, members, root)) {
            return -1;
        }
        checkMinimumCost(subordinates, members, root);
        return get<3>(members[root]);
    }
};

int main() {
    int N;
    cin >> N;
    vector<vector<int>> subordinates(N);
    vector<Member> members;
    int F, IN, IP, C;
    int root;
    for(int i = 0; i < N; ++ i) {
        cin >> F >> IN >> IP >> C;
        members.push_back(make_tuple(IN, IP, C, numeric_limits<int>::max(), false));
        if(F) {
            subordinates[F-1].push_back(i);
        }
        else {
            root = i;
        }
    }
    Solution s;
    cout << s.solve(subordinates, members, root) << endl;
    return 0;
}
