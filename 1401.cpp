#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

};

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> students;
    unordered_map<int, deque<pair<int, int>>> procedures;
    vector<int> office(M+1);
    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<tuple<int, int, int, int>>> gq;
    unordered_map<int, int> finish;

    for(int i = 0; i < N; ++ i) {
        int S, T, P;
        cin >> S >> T >> P;
        students.push_back(S);
        gq.push(make_tuple(T, S, 0, 0)); // student S arrived at time T, with office and need time information

        for(int j = 0; j < P; ++ j) {
            int O, W;
            cin >> O >> W;
            procedures[S].push_back(make_pair(O, W)); // add one procedure for student S
        }
    }

    while(!gq.empty()) { // global event queue
        int at, s, o, ct;
        tie(at, s, o, ct) = gq.top();
        gq.pop();

        int ft = max(office[o], at) + ct; // finish time at office o
        if(o) {
            office[o] = ft; // update office next service time
        }

        if(procedures[s].empty()) { // student s has finished
            finish[s] = ft;
        }
        else {
            auto next = procedures[s].front();
            procedures[s].pop_front();
            gq.push(make_tuple(ft + K, s, next.first, next.second));
        }
    }
    for(auto s : students) {
        cout << finish[s] << endl;
    }
    return 0;
}
