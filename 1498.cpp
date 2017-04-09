#include <bits/stdc++.h>
using namespace std;

using LL = long long int;
int main() {
    LL N, Q;
    cin >> N >> Q;
    LL M = 1;
    LL t = 0;
    while(true) {
        LL t1 = N % M == 0 ? N / M : N / M + 1;
        LL t2 = N % (2*M) == 0 ? N / (2*M) + Q: N / (2*M) + 1 + Q;
        if(t1 >= t2) {
            M *= 2;
            t += Q;
        }
        else {
            break;
        }
    }
    // let K members from M to fork themselves
    // let T tasks from N to be worked by the remaining (M - K) members
    // let Q + t be the finish time
    // then, (N - T) = 2tK, T/(M - K) = (Q + t)
    // this gives (M(Q + t) - N) = (Q - t)K
    // currently Q + t <= 2Q, which means M(Q + t) >= N
    // so Q + t >= N/M
    // so forking is not better than just do it, which consumes N/M time
    t += N / M;
    t += N % M != 0;
    cout << t << endl;
    return 0;
}
