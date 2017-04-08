#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    int A;
    int odd;
    int even;

    odd = even = 0;
    cin >> N;
    for(int i = 0; i < N; ++ i) {
        cin >> A;
        (A & 1) ? ++ odd : ++ even;
    }
    cout << abs(odd - even) << endl;

    return 0;
}
